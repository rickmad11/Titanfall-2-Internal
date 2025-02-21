#include "pch.h"
#include "DX11.h"

#include "font.h"

namespace MadRenderer
{
	DX11* DX11::Get()
	{
		static DX11 instance;
		return &instance;
	}
	
	void DX11::BeforeResize() noexcept
	{
		DX11* p_dx11 = Get();

		p_dx11->pDevice->Release();
		p_dx11->pDeviceContext->Release();
		(void)p_dx11->pRenderTargetView.Reset();

		p_dx11->pBlendState.Reset();
		p_dx11->pConstantProjectionMatrixBuffer.Reset();
		p_dx11->pInputLayout.Reset();
		p_dx11->pVertexBuffer.Reset();
		p_dx11->pNonPremultipliedState.Reset();
		p_dx11->common_states.reset();
	}

	void DX11::AfterResize(IDXGISwapChain* _pSwapChain) noexcept
	{
		if (_pSwapChain)
		{
			DX11* p_dx11 = Get();

			p_dx11->pSwapChain = _pSwapChain;

			p_dx11->InitializeDevices();
			p_dx11->SetWindowData();
			p_dx11->InitializeBackBuffer();

			p_dx11->GetForegroundRenderList()->Clear();
			p_dx11->GetForegroundRenderList()->Clear();

			p_dx11->InitializeVertexBuffer();
			p_dx11->SetConstantBuffer();

			p_dx11->SetBlendState();
			p_dx11->SetInputLayout();
			p_dx11->SetCommonState();
		}
	}

	bool DX11::Initialize(IDXGISwapChain* _pSwapChain)
	{
		if (_pSwapChain == nullptr)
			return false;
		
		pSwapChain = _pSwapChain;

		SetWindowData();

		if (windowHeight <= 0 || windowWidth <= 0)
			return false;

		if(!InitializeDevices())
		{
			MessageBoxW(nullptr, L"Error InitializeDevices \nbool DX11::Initialize()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		if(!InitializeBackBuffer())
		{
			MessageBoxW(nullptr, L"Error InitializeBackBuffer \nbool DX11::Initialize()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		if(!InitializePixelShader())
		{
			MessageBoxW(nullptr, L"Error InitializePixelShader \nbool DX11::Initialize()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		if(!InitializeVertexShader())
		{
			MessageBoxW(nullptr, L"Error InitializeVertexShader \nbool DX11::Initialize()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		if(!InitializeVertexBuffer())
		{
			MessageBoxW(nullptr, L"Error InitializeVertexBuffer \nbool DX11::Initialize()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}

		if(!InitializeRasterizerState())
		{
			MessageBoxW(nullptr, L"Error InitializeRasterizerState \nbool DX11::Initialize()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}

		SetConstantBuffer();
		SetInputLayout();
		SetBlendState();
		SetCommonState();
	
		InitializeFont();
	
		return true;
	}
	
	void DX11::Begin()
	{
		CaptureDirectX11State();

		pDeviceContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);

		D3D11_VIEWPORT d_viewport{};
		d_viewport.TopLeftX = 0.f;
		d_viewport.TopLeftY = 0.f;
		d_viewport.Width	= static_cast<float>(windowWidth);
		d_viewport.Height	= static_cast<float>(windowHeight);
		d_viewport.MinDepth = 0.f;
		d_viewport.MaxDepth = 1.f;

		pDeviceContext->RSSetViewports(1, &d_viewport);

		pDeviceContext->OMSetBlendState(pBlendState.Get(), nullptr, 0xffffffff);
		pDeviceContext->RSSetState(pRasterizerState.Get());

		pDeviceContext->VSSetConstantBuffers(0, 1, pConstantProjectionMatrixBuffer.GetAddressOf());

		pDeviceContext->PSSetShader(pPixelShader.Get(), nullptr, 0);
		pDeviceContext->VSSetShader(pVertexShader.Get(), nullptr, 0);
	
		pDeviceContext->IASetInputLayout(pInputLayout.Get());
	
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	
	}
	
	void DX11::End()
	{
		pBackGroundRenderList->Draw();
	
		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, pBlendState.Get(), nullptr, nullptr, pRasterizerState.Get(), nullptr);
		pBackGroundRenderList->Draw2DText();
		spriteBatch->End();
	
		pDeviceContext->PSSetShader(pPixelShader.Get(), nullptr, 0);
		pDeviceContext->VSSetShader(pVertexShader.Get(), nullptr, 0);
		pDeviceContext->IASetInputLayout(pInputLayout.Get());
	
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	
		pForegroundRenderList->Draw();
	
		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, pNonPremultipliedState.Get(), nullptr, nullptr, pRasterizerState.Get(), nullptr);
		pForegroundRenderList->Draw2DText();
		pTextureRenderList->DrawTexture();
		spriteBatch->End();
	
		pBackGroundRenderList->Clear();
		pForegroundRenderList->Clear();
		pTextureRenderList->Clear();

		RestoreDirectX11State();
	}
	
	RenderList* DX11::GetBackGroundRenderList() const noexcept
	{
		return pBackGroundRenderList.get();
	}
	
	RenderList* DX11::GetForegroundRenderList() const noexcept
	{
		return pForegroundRenderList.get();
	}
	
	TextureManager* DX11::GetTextureRenderList() const noexcept
	{
		return pTextureRenderList.get();
	}
	
	AudioManager* DX11::GetAudioManager() const noexcept
	{
		return pAudioManager.get();
	}

	void DX11::ChangeFont(std::uint8_t* const pData, std::size_t size) noexcept
	{
		spriteBatch.reset();
		spriteFont.reset();
	
		spriteBatch = std::make_unique<DirectX::SpriteBatch>(pDeviceContext);
		spriteFont = std::make_unique<DirectX::SpriteFont>(pDevice, pData, size, false);
	}
	
	void DX11::AddVertices(RenderList* const pRenderList, std::span<Vertex> vertices, D3D11_PRIMITIVE_TOPOLOGY topology) const 
	{
		if (vertices.size() > RenderList::MaxVertices)
			pRenderList->ClampBuffer();
	
		pRenderList->batches.emplace_back(vertices.size(), topology);
	
		pRenderList->vertices.resize(pRenderList->vertices.size() + vertices.size());
		std::memcpy(&pRenderList->vertices[pRenderList->vertices.size() - vertices.size()], vertices.data(), vertices.size() * sizeof(Vertex));
	}
	
	bool DX11::InitializeDevices()
	{
		HRESULT device_result = pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pDevice));

		if(device_result != S_OK)
		{
			MessageBoxW(nullptr, L"Error GetDevice \nbool DX11::InitializeDevices(IDXGISwapChain* pSwapChain)", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}

		pDevice->GetImmediateContext(&pDeviceContext);

		return true;
	}
	
	bool DX11::InitializeBackBuffer()
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> pID3D11Texture2D = nullptr;
		HRESULT buffer_result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pID3D11Texture2D.GetAddressOf()));
	
		if(buffer_result != S_OK)
		{
			MessageBoxW(nullptr, L"Error GetBuffer \nbool DX11::InitializeBackBuffer()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
		
		HRESULT render_view_result = pDevice->CreateRenderTargetView(pID3D11Texture2D.Get(), nullptr, pRenderTargetView.GetAddressOf());
		
		if (render_view_result != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateRenderTargetView \nbool DX11::InitializeBackBuffer()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		return true;
	}
	
	bool DX11::InitializePixelShader()
	{
		static constexpr char pixel_shader_code[]
		{
			R"(
				struct PixelInputType
				{
				    float4 position : SV_POSITION;
				    float4 color : COLOR;
				};
	
				float4 ColorPixelShader(PixelInputType input) : SV_Target
				{
				    return input.color;
				}
			)"
		};
	
		HRESULT compile_result = D3DCompile(pixel_shader_code, std::size(pixel_shader_code), "PixelShader", nullptr,
											nullptr, "ColorPixelShader", "ps_5_0", NULL,
											NULL, pPixelShaderBlob.GetAddressOf(), nullptr);
	
		if(compile_result != S_OK)
		{
			MessageBoxW(nullptr, L"Error D3DCompile \nbool DX11::InitializePixelShader()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		HRESULT result_pixel_shader = pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, pPixelShader.GetAddressOf());
	
		if (result_pixel_shader != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreatePixelShader \nbool DX11::InitializePixelShader()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		return true;
	}
	
	bool DX11::InitializeVertexShader()
	{
		static constexpr char vertex_shader_code[]
		{
			R"(
				struct VS_INPUT
				{
				    float3 position : POSITION; 
				    float4 color : COLOR;       
				};
	
				struct VS_OUTPUT
				{
				    float4 position : SV_POSITION; 
				    float4 color : COLOR;          
				};
	
				cbuffer TransformBuffer : register(b0)
				{
				    matrix worldViewProj;  
				};
	
				VS_OUTPUT main(VS_INPUT input)
				{
				    VS_OUTPUT output;
	
				    output.position = mul(worldViewProj, float4(input.position, 1.0f));
				    output.color = float4(input.color.rgb / 255.0f, input.color.a / 255.0f); //divide 255 for normalized colors to support simple RGB google paste, keep a for blend state
				
				    return output;
				}
			)"
		};
	
		HRESULT compile_result = D3DCompile(vertex_shader_code, std::size(vertex_shader_code), "VertexShader", nullptr,
											nullptr, "main", "vs_5_0", NULL,
											NULL, pVertexShaderBlob.GetAddressOf(), nullptr);
	
		if (compile_result != S_OK)
		{
			MessageBoxW(nullptr, L"Error D3DCompile \nbool DX11::InitializeVertexShader()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		HRESULT result_vertex_shader = pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf());
	
		if (result_vertex_shader != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateVertexShader \nbool DX11::InitializeVertexShader()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		return true;
	}

	bool DX11::InitializeRasterizerState()
	{
		D3D11_RASTERIZER_DESC rasterizer_desc{};
		rasterizer_desc.AntialiasedLineEnable = true;
		rasterizer_desc.CullMode = D3D11_CULL_NONE;
		rasterizer_desc.DepthBias = 0;
		rasterizer_desc.DepthBiasClamp = 0.0f;
		rasterizer_desc.DepthClipEnable = true;
		rasterizer_desc.FillMode = D3D11_FILL_SOLID;
		rasterizer_desc.FrontCounterClockwise = false;
		rasterizer_desc.MultisampleEnable = false;
		rasterizer_desc.ScissorEnable = false;
		rasterizer_desc.SlopeScaledDepthBias = 0.0f;

		HRESULT rasterizer_result = pDevice->CreateRasterizerState(&rasterizer_desc, pRasterizerState.GetAddressOf());

		if (rasterizer_result != S_OK)
		{
			OutputDebugStringW(L"\n\n\nCannot CreateRasterizerState\n\n\n");
			return false;
		}

		return true;
	}

	bool DX11::InitializeVertexBuffer()
	{
		D3D11_BUFFER_DESC buffer_desc{};
		buffer_desc.ByteWidth			= sizeof(Vertex) * static_cast<UINT>(RenderList::MaxVertices);
		buffer_desc.Usage				= D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
		buffer_desc.MiscFlags			= 0;
		buffer_desc.StructureByteStride = 0;
	
		HRESULT constant_buffer_status = pDevice->CreateBuffer(&buffer_desc, nullptr, pVertexBuffer.GetAddressOf());
	
		if (constant_buffer_status != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateBuffer \nbool DX11::InitializeVertexBuffer()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		return true;
	}
	
	void DX11::InitializeFont()
	{
		spriteBatch = std::make_unique<DirectX::SpriteBatch>(pDeviceContext);
		spriteFont = std::make_unique<DirectX::SpriteFont>(pDevice, DefaultFontBuffer, sizeof(DefaultFontBuffer), false);
	}
	
	void DX11::SetCommonState()
	{
		common_states = std::make_unique<DirectX::CommonStates>(pDevice);
		pNonPremultipliedState = common_states->NonPremultiplied();
	}

	void DX11::SetWindowData()
	{
		DXGI_SWAP_CHAIN_DESC swap_chain_desc {};

		HRESULT result = pSwapChain->GetDesc(&swap_chain_desc);

		if(result != S_OK)
		{
			MessageBoxW(nullptr, L"Error SetWindowData \nvoid DX11::SetWindowData()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return;
		}

		windowHandle = swap_chain_desc.OutputWindow;

		RECT window_rect {};
		GetClientRect(windowHandle, &window_rect);

		windowHeight = window_rect.bottom - window_rect.top;
		windowWidth  = window_rect.right - window_rect.left;
	}

	FORCEINLINE void DX11::CaptureDirectX11State() noexcept
	{
		//Pasted from the legendary Dear ImGui https://github.com/ocornut/imgui/blob/87f3109c1af835be0e5b4b4410baa1c66ced7b33/backends/imgui_impl_dx11.cpp#L205

		(void)memset(&previous_pipeline_state, 0, sizeof(BACKUP_DX11_STATE));

		previous_pipeline_state.ScissorRectsCount = previous_pipeline_state.ViewportsCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
		pDeviceContext->RSGetScissorRects(&previous_pipeline_state.ScissorRectsCount, previous_pipeline_state.ScissorRects);

		pDeviceContext->RSGetViewports(&previous_pipeline_state.ViewportsCount, previous_pipeline_state.Viewports);

		pDeviceContext->RSGetState(&previous_pipeline_state.RS);

		pDeviceContext->OMGetBlendState(&previous_pipeline_state.BlendState, previous_pipeline_state.BlendFactor, &previous_pipeline_state.SampleMask);

		pDeviceContext->OMGetDepthStencilState(&previous_pipeline_state.DepthStencilState, &previous_pipeline_state.StencilRef);

		pDeviceContext->PSGetShaderResources(0, 1, &previous_pipeline_state.PSShaderResource);

		pDeviceContext->PSGetSamplers(0, 1, &previous_pipeline_state.PSSampler);

		previous_pipeline_state.PSInstancesCount = previous_pipeline_state.VSInstancesCount = previous_pipeline_state.GSInstancesCount = 256;

		pDeviceContext->PSGetShader(&previous_pipeline_state.PS, previous_pipeline_state.PSInstances, &previous_pipeline_state.PSInstancesCount);

		pDeviceContext->VSGetShader(&previous_pipeline_state.VS, previous_pipeline_state.VSInstances, &previous_pipeline_state.VSInstancesCount);

		pDeviceContext->VSGetConstantBuffers(0, 1, &previous_pipeline_state.VSConstantBuffer);

		pDeviceContext->GSGetShader(&previous_pipeline_state.GS, previous_pipeline_state.GSInstances, &previous_pipeline_state.GSInstancesCount);

		pDeviceContext->IAGetPrimitiveTopology(&previous_pipeline_state.PrimitiveTopology);

		pDeviceContext->IAGetIndexBuffer(&previous_pipeline_state.IndexBuffer, &previous_pipeline_state.IndexBufferFormat, &previous_pipeline_state.IndexBufferOffset);

		pDeviceContext->IAGetVertexBuffers(0, 1, &previous_pipeline_state.VertexBuffer, &previous_pipeline_state.VertexBufferStride, &previous_pipeline_state.VertexBufferOffset);

		pDeviceContext->IAGetInputLayout(&previous_pipeline_state.InputLayout);
	}

	FORCEINLINE void DX11::RestoreDirectX11State() const noexcept
	{
		//Pasted from the legendary Dear ImGui https://github.com/ocornut/imgui/blob/87f3109c1af835be0e5b4b4410baa1c66ced7b33/backends/imgui_impl_dx11.cpp#L205

		pDeviceContext->RSSetScissorRects(previous_pipeline_state.ScissorRectsCount, previous_pipeline_state.ScissorRects);

		pDeviceContext->RSSetViewports(previous_pipeline_state.ViewportsCount, previous_pipeline_state.Viewports);

		pDeviceContext->RSSetState(previous_pipeline_state.RS);
		if (previous_pipeline_state.RS) previous_pipeline_state.RS->Release();

		pDeviceContext->OMSetBlendState(previous_pipeline_state.BlendState, previous_pipeline_state.BlendFactor, previous_pipeline_state.SampleMask);
		if (previous_pipeline_state.BlendState) previous_pipeline_state.BlendState->Release();

		pDeviceContext->OMSetDepthStencilState(previous_pipeline_state.DepthStencilState, previous_pipeline_state.StencilRef);
		if (previous_pipeline_state.DepthStencilState) previous_pipeline_state.DepthStencilState->Release();

		pDeviceContext->PSSetShaderResources(0, 1, &previous_pipeline_state.PSShaderResource);
		if (previous_pipeline_state.PSShaderResource) previous_pipeline_state.PSShaderResource->Release();

		pDeviceContext->PSSetSamplers(0, 1, &previous_pipeline_state.PSSampler);
		if (previous_pipeline_state.PSSampler) previous_pipeline_state.PSSampler->Release();

		pDeviceContext->PSSetShader(previous_pipeline_state.PS, previous_pipeline_state.PSInstances, previous_pipeline_state.PSInstancesCount);
		if (previous_pipeline_state.PS) previous_pipeline_state.PS->Release();

		for (UINT i = 0; i < previous_pipeline_state.PSInstancesCount; i++)
			if (previous_pipeline_state.PSInstances[i]) previous_pipeline_state.PSInstances[i]->Release();

		pDeviceContext->VSSetShader(previous_pipeline_state.VS, previous_pipeline_state.VSInstances, previous_pipeline_state.VSInstancesCount);
		if (previous_pipeline_state.VS) previous_pipeline_state.VS->Release();

		pDeviceContext->VSSetConstantBuffers(0, 1, &previous_pipeline_state.VSConstantBuffer);
		if (previous_pipeline_state.VSConstantBuffer) previous_pipeline_state.VSConstantBuffer->Release();

		pDeviceContext->GSSetShader(previous_pipeline_state.GS, previous_pipeline_state.GSInstances, previous_pipeline_state.GSInstancesCount);
		if (previous_pipeline_state.GS) previous_pipeline_state.GS->Release();

		for (UINT i = 0; i < previous_pipeline_state.VSInstancesCount; i++)
			if (previous_pipeline_state.VSInstances[i]) previous_pipeline_state.VSInstances[i]->Release();

		pDeviceContext->IASetPrimitiveTopology(previous_pipeline_state.PrimitiveTopology);

		pDeviceContext->IASetIndexBuffer(previous_pipeline_state.IndexBuffer, previous_pipeline_state.IndexBufferFormat, previous_pipeline_state.IndexBufferOffset);
		if (previous_pipeline_state.IndexBuffer) previous_pipeline_state.IndexBuffer->Release();

		pDeviceContext->IASetVertexBuffers(0, 1, &previous_pipeline_state.VertexBuffer, &previous_pipeline_state.VertexBufferStride, &previous_pipeline_state.VertexBufferOffset);
		if (previous_pipeline_state.VertexBuffer) previous_pipeline_state.VertexBuffer->Release();

		pDeviceContext->IASetInputLayout(previous_pipeline_state.InputLayout);
		if (previous_pipeline_state.InputLayout) previous_pipeline_state.InputLayout->Release();

	}
	
	void DX11::SetConstantBuffer()
	{
		D3D11_BUFFER_DESC buffer_desc {};
		buffer_desc.ByteWidth			= sizeof(DirectX::SimpleMath::Matrix);
		buffer_desc.Usage				= D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
		buffer_desc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
		buffer_desc.MiscFlags			= 0;
		buffer_desc.StructureByteStride = 0;
	
		UINT numViewports = 1;
		D3D11_VIEWPORT viewport{};
		pDeviceContext->RSGetViewports(&numViewports, &viewport);
	
		projection_matrix = DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter(viewport.TopLeftX, viewport.Width, viewport.Height, viewport.TopLeftY,
			viewport.MinDepth, viewport.MaxDepth);
	
		D3D11_SUBRESOURCE_DATA subresource_data {};
		subresource_data.pSysMem = &projection_matrix;
	
		HRESULT constant_buffer_status = pDevice->CreateBuffer(&buffer_desc, &subresource_data, pConstantProjectionMatrixBuffer.GetAddressOf());
	
		if (constant_buffer_status != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateBuffer \nvoid DX11::SetConstantBuffer()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return;
		}
	}
	
	void DX11::SetInputLayout()
	{
		constexpr D3D11_INPUT_ELEMENT_DESC input_element_desc[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
	
		HRESULT input_layout_result = pDevice->CreateInputLayout(&input_element_desc[0], std::size(input_element_desc), pVertexShaderBlob->GetBufferPointer(),
			pVertexShaderBlob->GetBufferSize(), pInputLayout.GetAddressOf());
	
		if(input_layout_result != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateInputLayout \nvoid DX11::SetInputLayout()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return;
		}
	}
	
	void DX11::SetBlendState()
	{
		D3D11_BLEND_DESC blendDesc = {};
		blendDesc.AlphaToCoverageEnable = 0;
		blendDesc.IndependentBlendEnable = 0;
	
		blendDesc.RenderTarget[0].BlendEnable = 1;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT blend_result = pDevice->CreateBlendState(&blendDesc, pBlendState.GetAddressOf());
	
		if(blend_result != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateBlendState \nvoid DX11::SetBlendState()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return;
		}
	}
	
	void RenderList::Draw() const noexcept
	{
		if (vertices.empty())
			return;
	
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		pRenderer->pDeviceContext->Map(pRenderer->pVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		std::memcpy(mappedResource.pData, vertices.data(), vertices.size() * sizeof(Vertex));
		pRenderer->pDeviceContext->Unmap(pRenderer->pVertexBuffer.Get(), 0);
	
		std::size_t pos = 0;
		for (auto const& batch : batches)
		{
			pRenderer->pDeviceContext->IASetPrimitiveTopology(batch.topology);
			pRenderer->pDeviceContext->Draw(static_cast<UINT>(batch.count), static_cast<UINT>(pos));
	
			pos += batch.count;
		}
	}
	
	void RenderList::DrawLine(Vector2 from, Vector2 to, Color const& color) noexcept
	{
		Vertex _vertices[2]
		{
			{ {from.x, from.y, 0.f} , color },
			{ {to.x, to.y, 0.f}, color }
		};
	
		pRenderer->AddVertices(this, _vertices, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	}
	
	void RenderList::DrawDot(Vector2 pos, Color const& color) noexcept
	{
		DrawFilledRect({ pos.x, pos.y, 2.f, 2.f }, color);
	}
	
	void RenderList::DrawFilledRect(Vector4 const& rect, Color const& color) noexcept
	{
		Vertex _vertices[6]
		{
			{ {rect.x, rect.y, 0.f}, color },
			{ {rect.x + rect.z, rect.y, 0.f}, color },
			{ {rect.x, rect.y + rect.w, 0.f}, color },
	
			{ {rect.x + rect.z, rect.y, 0.f}, color },
			{ {rect.x + rect.z, rect.y + rect.w, 0.f}, color },
			{ {rect.x, rect.y + rect.w, 0.f}, color }
		};
	
		pRenderer->AddVertices(this, _vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	
	void RenderList::DrawRect(Vector4 const& rect, float strokeWidth, Color const& color) noexcept
	{
		DirectX::XMFLOAT4 tmp = rect;
		tmp.z = strokeWidth;
		DrawFilledRect(tmp, color);
		tmp.x = rect.x + rect.z - strokeWidth;
		DrawFilledRect(tmp, color);
		tmp.z = rect.z;
		tmp.x = rect.x;
		tmp.w = strokeWidth;
		DrawFilledRect(tmp, color);
		tmp.y = rect.y + rect.w;
		DrawFilledRect(tmp, color);
	}
	
	void RenderList::DrawOutlinedFilledRect(Vector4 const& rect, float strokeWidth, Color const& OutlineColor, Color const& color) noexcept
	{
		DrawFilledRect(rect, color);
		DrawRect(rect, strokeWidth, OutlineColor);
	}
	
	void RenderList::DrawFilledRectGradient(Vector4 const& rect, Color color, float gradientIntensity) noexcept
	{
		float scaleFactor = 1.0f - gradientIntensity;
	
		Color color2 = Color{ color.x * (0.8f + scaleFactor * 0.2f), color.y * (0.8f + scaleFactor * 0.2f), color.z * (0.8f + scaleFactor * 0.2f), color.w };
		Color color3 = Color{ color.x * (0.6f + scaleFactor * 0.4f), color.y * (0.6f + scaleFactor * 0.4f), color.z * (0.6f + scaleFactor * 0.4f), color.w };
		Color color4 = Color{ color.x * (0.4f + scaleFactor * 0.6f), color.y * (0.4f + scaleFactor * 0.6f), color.z * (0.4f + scaleFactor * 0.6f), color.w };
	
		Vertex _vertices[6]
		{
			{ {rect.x, rect.y, 0.f}, color },     
			{ {rect.x + rect.z, rect.y, 0.f}, color2 },
			{ {rect.x, rect.y + rect.w, 0.f}, color3 }, 
	
			{ {rect.x + rect.z, rect.y, 0.f}, color2 },
			{ {rect.x + rect.z, rect.y + rect.w, 0.f}, color4 }, 
			{ {rect.x, rect.y + rect.w, 0.f}, color3 }, 
		};
	
		pRenderer->AddVertices(this, _vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	
	void RenderList::DrawOutlinedRect(Vector4 const& rect, float strokeWidth, Color const& OutlineColor) noexcept
	{
		DirectX::XMFLOAT4 tmp = rect;
		tmp.z = strokeWidth;  
		DrawFilledRect(tmp, OutlineColor);
		tmp.x = rect.x + rect.z - strokeWidth;  
		DrawFilledRect(tmp, OutlineColor);
		tmp = rect;
		tmp.w = strokeWidth;  
		DrawFilledRect(tmp, OutlineColor);
		tmp.y = rect.y + rect.w - strokeWidth; 
		DrawFilledRect(tmp, OutlineColor);
	}

	void RenderList::DrawRect(Vector4 const& rect, Color const& InsideColor, Color const& OutlineColor) noexcept
	{
		const Vector2 topLeft(rect.x, rect.y);
		const Vector2 topRight(rect.x + rect.z, rect.y);
		const Vector2 bottomLeft(rect.x, rect.y + rect.w);
		const Vector2 bottomRight(rect.x + rect.z, rect.y + rect.w);

		DrawLine(topLeft, topRight, OutlineColor);                    // Top
		DrawLine(bottomLeft, bottomRight, OutlineColor);              // Bottom 
		DrawLine(topLeft, bottomLeft, OutlineColor);                  // Left 
		DrawLine(topRight, bottomRight, OutlineColor);                // Right 

		DrawLine({ topLeft.x + 1, topLeft.y + 1 }, { topRight.x - 1, topRight.y + 1 }, InsideColor);
		DrawLine({ bottomLeft.x + 1, bottomLeft.y - 1 }, { bottomRight.x - 1, bottomRight.y - 1 }, InsideColor);
		DrawLine({ topLeft.x + 1, topLeft.y + 1 }, { bottomLeft.x + 1, bottomLeft.y - 1 }, InsideColor);
		DrawLine({ topRight.x - 1, topRight.y + 1 }, { bottomRight.x - 1, bottomRight.y - 1 }, InsideColor);

		DrawLine({ topLeft.x + 2, topLeft.y + 2 }, { topRight.x - 2, topRight.y + 2 }, OutlineColor);
		DrawLine({ bottomLeft.x + 2, bottomLeft.y - 2 }, { bottomRight.x - 2, bottomRight.y - 2 }, OutlineColor);
		DrawLine({ topLeft.x + 2, topLeft.y + 2 }, { bottomLeft.x + 2, bottomLeft.y - 2 }, OutlineColor);
		DrawLine({ topRight.x - 2, topRight.y + 2 }, { bottomRight.x - 2, bottomRight.y - 2 }, OutlineColor);
	}

	void RenderList::DrawRect(Vector4 const& rect, float strokeWidth, Color const& InsideColor, Color const& OutlineColor) noexcept
	{
		const Vector2 topLeft(rect.x, rect.y);
		const Vector2 topRight(rect.x + rect.z, rect.y);
		const Vector2 bottomLeft(rect.x, rect.y + rect.w);
		const Vector2 bottomRight(rect.x + rect.z, rect.y + rect.w);

		for (float i = 0; i < strokeWidth; i++)
		{
			DrawLine({ topLeft.x + i, topLeft.y + i }, { topRight.x - i, topRight.y + i }, OutlineColor);
			DrawLine({ bottomLeft.x + i, bottomLeft.y - i }, { bottomRight.x - i, bottomRight.y - i }, OutlineColor);
			DrawLine({ topLeft.x + i, topLeft.y + i }, { bottomLeft.x + i, bottomLeft.y - i }, OutlineColor);
			DrawLine({ topRight.x - i, topRight.y + i }, { bottomRight.x - i, bottomRight.y - i }, OutlineColor);
		}

		for (float i = strokeWidth; i < 2 * strokeWidth; i++)
		{
			DrawLine({ topLeft.x + i, topLeft.y + i }, { topRight.x - i, topRight.y + i }, InsideColor);
			DrawLine({ bottomLeft.x + i, bottomLeft.y - i }, { bottomRight.x - i, bottomRight.y - i }, InsideColor);
			DrawLine({ topLeft.x + i, topLeft.y + i }, { bottomLeft.x + i, bottomLeft.y - i }, InsideColor);
			DrawLine({ topRight.x - i, topRight.y + i }, { bottomRight.x - i, bottomRight.y - i }, InsideColor);
		}

		for (float i = 2 * strokeWidth; i < 3 * strokeWidth; i++)
		{
			DrawLine({ topLeft.x + i, topLeft.y + i }, { topRight.x - i, topRight.y + i }, OutlineColor);
			DrawLine({ bottomLeft.x + i, bottomLeft.y - i }, { bottomRight.x - i, bottomRight.y - i }, OutlineColor);
			DrawLine({ topLeft.x + i, topLeft.y + i }, { bottomLeft.x + i, bottomLeft.y - i }, OutlineColor);
			DrawLine({ topRight.x - i, topRight.y + i }, { bottomRight.x - i, bottomRight.y - i }, OutlineColor);
		}
	}

	void RenderList::DrawCircle(Vector2 pos, float radius, Color const& color) noexcept
	{
		constexpr int segments = 24;
	
		Vertex _vertices[segments + 1];
	
		constexpr float angleIncrement = DirectX::XM_2PI / segments;
	
		float x = radius, y = 0.0f;
	
		float cosTheta = std::cos(angleIncrement);
		float sinTheta = std::sin(angleIncrement);
	
		for (int i = 0; i <= segments; ++i) {
	
			_vertices[i] = Vertex{
				{pos.x + x, pos.y + y, 0.f},
				color
			};
	
			float newX = x * cosTheta - y * sinTheta;
			y = x * sinTheta + y * cosTheta;
			x = newX;
		}
	
		pRenderer->AddVertices(this, _vertices, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}
	
	void RenderList::Draw2DText() const noexcept
	{
		if (text_buffer.empty() || text_data.empty())
			return;
	
		if (text_buffer.size() != text_data.size())
			return;
	
		DirectX::SpriteBatch* p_SpriteBatch = pRenderer->spriteBatch.get();
	
		std::size_t pos = 0;
		for (std::pair<std::string, Vector2> const& text : text_buffer)
		{
			pRenderer->spriteFont->DrawString(p_SpriteBatch, text.first.c_str(), text.second, text_data[pos].first, 0.f, {}, text_data[pos].second);
			++pos;
		}
	
	}
	
	void RenderList::DrawString(const char* string, Vector2 pos, Color color, float scale) noexcept
	{
		static constexpr float normal_color_conversion = 1.f / 255.f;
		color = Color{color.x * normal_color_conversion, color.y * normal_color_conversion, color.z * normal_color_conversion, color.w};
	
		text_buffer.emplace_back(string, pos);
		text_data.emplace_back(color, scale);
	}

	void RenderList::DrawOutlinedString(const char* string, Vector2 pos, Color color, float scale) noexcept
	{
		static constexpr float normal_color_conversion = 1.f / 255.f;
		color = Color{ color.x * normal_color_conversion, color.y * normal_color_conversion, color.z * normal_color_conversion, color.w };

		text_buffer.emplace_back(string, pos + Vector2{1, 1});
		text_data.emplace_back(Color{0, 0, 0, 255}, scale);

		text_buffer.emplace_back(string, pos + Vector2{ -1, 1 });
		text_data.emplace_back(Color{ 0, 0, 0, 255 }, scale);

		text_buffer.emplace_back(string, pos + Vector2{ -1, -1 });
		text_data.emplace_back(Color{ 0, 0, 0, 255 }, scale);

		text_buffer.emplace_back(string, pos + Vector2{ 1, -1 });
		text_data.emplace_back(Color{ 0, 0, 0, 255 }, scale);

		text_buffer.emplace_back(string, pos);
		text_data.emplace_back(color, scale);
	}

	RenderList::Vector2 RenderList::MeasureString(const char* string, bool ignore_whitespace) const noexcept
	{
		return pRenderer->spriteFont->MeasureString(string, ignore_whitespace);
	}
	
	void TextureManager::ClampTextureBuffer() noexcept
	{
		if (textures.size() > MaxTextureCount)
			textures.erase(std::next(textures.begin(), MaxTextureCount), textures.end());
	}
	
	void TextureManager::ClearAllTextures() noexcept
	{
		textures.clear();
	}
	
	void TextureManager::OnResize() noexcept
	{
		std::vector<std::pair<const int, std::size_t>> temp_texture_data;
	
		for (std::pair<const int, TextureData>& curr : textures)
			temp_texture_data.emplace_back(curr.first, curr.second.buffer_size);
	
		ClearAllTextures();
	
		for (std::pair<const int, void const*> const& memory_texture_file : memory_texture_file_map)
		{
			for (std::pair<const int, std::size_t>& curr : temp_texture_data)
			{
				if(curr.first == memory_texture_file.first)
				{
					TextureData texture_data;
					HRESULT result = DirectX::CreateWICTextureFromMemory(pRenderer->pDevice, static_cast<std::uint8_t const*>(memory_texture_file.second), curr.second,
						texture_data.pTextureResource.GetAddressOf(), texture_data.pTextureResourceView.GetAddressOf());
	
					if (result != S_OK)
						MessageBoxW(nullptr, L"Error CreateWICTextureFromMemory \nvoid TextureManager::OnResize() noexcept", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
	
					texture_data.buffer_size = curr.second;
					textures[curr.first] = texture_data;
	
					break;
				}
			}
		}
	
		for (std::pair<const int, std::wstring>& texture_file : texture_file_map)
		{
			for (std::pair<const int, std::size_t>& curr : temp_texture_data)
			{
				if(curr.first == texture_file.first)
				{
					TextureData texture_data;
					HRESULT result = DirectX::CreateWICTextureFromFile(pRenderer->pDevice, texture_file.second.c_str(),
						texture_data.pTextureResource.GetAddressOf(), texture_data.pTextureResourceView.GetAddressOf());
	
					if (result != S_OK)
						MessageBoxW(nullptr, L"Error CreateWICTextureFromFile \nvoid TextureManager::OnResize() noexcept", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
	
					textures[curr.first] = texture_data;
	
					break;
				}
			}
		}
	}
	
	int TextureManager::AddTexture(const wchar_t* file) noexcept
	{
		for (const auto& pair : texture_file_map)
		{
			if (pair.second == file)
			{
				return pair.first;  
			}
		}
	
		TextureData texture_data;
		HRESULT result = DirectX::CreateWICTextureFromFile(pRenderer->pDevice, file, texture_data.pTextureResource.GetAddressOf(), texture_data.pTextureResourceView.GetAddressOf());
	
		if (result != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateWICTextureFromFile \nint TextureManager::AddTexture(const wchar_t* file) noexcept", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return -1;
		}
	
		int texture_id = internal_texture_id++;
		textures[texture_id] = texture_data;
		texture_file_map[texture_id] = file;
	
		return texture_id;
	}
	
	int TextureManager::AddTexture(const char* file) noexcept
	{
		std::string temp { file };
		std::wstring wconverted { temp.begin(), temp.end() };
		return AddTexture(wconverted.c_str());
	}
	
	int TextureManager::AddTexture(const uint8_t* buffer, std::size_t size) noexcept
	{
		for (const auto& pair : memory_texture_file_map)
		{
			if (pair.second == buffer)
			{
				return pair.first;
			}
		}
	
		TextureData texture_data;
		HRESULT result = DirectX::CreateWICTextureFromMemory(pRenderer->pDevice, buffer, size, texture_data.pTextureResource.GetAddressOf(), texture_data.pTextureResourceView.GetAddressOf());
	
		if (result != S_OK)
		{
			MessageBoxW(nullptr, L"Error CreateWICTextureFromMemory \nint TextureManager::AddTexture(const uint8_t* buffer, std::size_t size) noexcept", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return -1;
		}
	
		texture_data.buffer_size = size;
	
		int texture_id = internal_texture_id++;
		textures[texture_id] = texture_data;
		memory_texture_file_map[texture_id] = reinterpret_cast<void const*>(buffer);
	
		return texture_id;
	}
	
	void TextureManager::DrawTexture(Vector2 pos, Color color, int texture_id, Vector2 scale)
	{
		if (textures.find(texture_id) != textures.end())
			texture_draw_data.emplace_back(pos, scale, color, texture_id);
	}

	void TextureManager::DrawTexture(Vector2 pos, int texture_id, Color color, Vector2 scale)
	{
		DrawTexture(pos, color, texture_id, scale);
	}

	TextureManager::Vector2 TextureManager::GetTextureSize(int texture_id) noexcept
	{
		TextureData& texture_data = textures.at(texture_id);

		Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture;
		texture_data.pTextureResource.As(&_texture);

		CD3D11_TEXTURE2D_DESC _textureDesc;
		_texture->GetDesc(&_textureDesc);

		return { static_cast<float>(_textureDesc.Width) * 0.5f, static_cast<float>(_textureDesc.Height) * 0.5f };
	}
	
	void TextureManager::DrawTexture() noexcept
	{
		if (texture_draw_data.empty())
			return;
	
		DirectX::SpriteBatch* pSpriteBatch = pRenderer->spriteBatch.get();
		for (TextureDrawData const& texture : texture_draw_data)
			pSpriteBatch->Draw(textures.at(texture.texture_id).pTextureResourceView.Get(), texture.pos, nullptr, texture.color, 0.f, {}, texture.texture_scaling);
	}
	
	void TextureManager::Clear() noexcept
	{
		if (!texture_draw_data.empty())
			texture_draw_data.clear();
	}
	
	bool AudioManager::InitializeAudioManager()
	{
		HRESULT result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	
		if (result != S_OK)
		{
			MessageBoxW(nullptr, L"Error CoInitializeEx \nbool AudioManager::InitializeAudioManager()", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return false;
		}
	
		pAudioEngine = std::make_unique<DirectX::AudioEngine>();
	
		return true;
	}
	
	int AudioManager::AddSoundEffect(const wchar_t* wavFile)
	{
		if(wavFile == nullptr)
		{
			//MessageBoxW(nullptr, L"Error wavFile was nullptr \nint AudioManager::AddSoundEffect(const wchar_t* wavFile)", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return -1;
		}
	
		if (internal_audio_id + 1 > MaxAudioCount)
		{
			//MessageBoxW(nullptr, L"Error max audio files reached \nint AudioManager::AddSoundEffect(const wchar_t* wavFile)", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return -1;
		}
	
		SoundData sound_data {};
		sound_data.wav_file = wavFile;
		sound_data.pSoundEffect = std::make_unique<DirectX::SoundEffect>(pAudioEngine.get(), wavFile);
	
		int sound_id = internal_audio_id++;
		sound_effects[sound_id] = std::move(sound_data);
	
		return sound_id;
	}

	int AudioManager::AddSoundEffect(const uint8_t* buffer, std::size_t size)
	{
		if (buffer == nullptr)
		{
			//MessageBoxW(nullptr, L"Error wavFile was nullptr \nint AudioManager::AddSoundEffect(const wchar_t* wavFile)", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return -1;
		}

		if (internal_audio_id + 1 > MaxAudioCount)
		{
			//MessageBoxW(nullptr, L"Error max audio files reached \nint AudioManager::AddSoundEffect(const wchar_t* wavFile)", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return -1;
		}

		std::unique_ptr<uint8_t[]> wavData = std::make_unique_for_overwrite<uint8_t[]>(size + sizeof(WAVEFORMATEX));
		std::memcpy(wavData.get(), buffer, size);

#pragma pack(push, 1)
		struct wav_header {
			std::uint32_t ChunkID;     
			std::uint32_t ChunkSize;   
			std::uint32_t Format;
			std::uint32_t Subchunk1ID;
			std::uint32_t Subchunk1Size;
			std::uint16_t AudioFormat; 
			std::uint16_t NumChannels; 
			std::uint32_t SampleRate;  
			std::uint32_t ByteRate;    
			std::uint16_t BlockAlign;  
			std::uint16_t BitsPerSample;
			std::uint32_t Subchunk2ID;
			std::uint32_t Subchunk2Size;
			//Data
		};
#pragma pack(pop)

		wav_header* p_wav_header = reinterpret_cast<wav_header*>(wavData.get());

		SoundData sound_data{};
		sound_data.wavFormat.cbSize = sizeof(WAVEFORMATEX);
		sound_data.wavFormat.nBlockAlign = p_wav_header->BlockAlign;
		sound_data.wavFormat.nChannels = p_wav_header->NumChannels;
		sound_data.wavFormat.nSamplesPerSec = p_wav_header->SampleRate;
		sound_data.wavFormat.wBitsPerSample = p_wav_header->BitsPerSample;
		sound_data.wavFormat.wFormatTag = WAVE_FORMAT_PCM;
		sound_data.wavFormat.nAvgBytesPerSec = p_wav_header->ByteRate;

		sound_data.pSoundEffect = std::make_unique<DirectX::SoundEffect>(pAudioEngine.get(), wavData, &sound_data.wavFormat, wavData.get() + sizeof(wav_header), p_wav_header->ChunkSize);

		int sound_id = internal_audio_id++;
		sound_effects[sound_id] = std::move(sound_data);

		return sound_id;
	}
	
	void AudioManager::PlaySoundEffect(int soundID, float volume, float pitch, float pan)
	{
		if(soundID == -1)
		{
			MessageBoxW(nullptr, L"Error invalid sound ID \nvoid AudioManager::PlaySoundEffect(int soundID, float volume, float pitch, float pan)", L"FATAL ERROR", MB_OKCANCEL | MB_ICONERROR);
			return;
		}
	
		if(soundID < sound_effects.size())
			sound_effects[soundID].pSoundEffect->Play(volume, pitch, pan);
	}
}
