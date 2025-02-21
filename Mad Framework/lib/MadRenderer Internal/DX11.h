#pragma once

namespace MadRenderer
{

	struct Vertex
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Color col;
	};

	struct Batch
	{
		std::size_t count;
		D3D11_PRIMITIVE_TOPOLOGY topology;
	};

	struct RenderList final
	{
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector4 = DirectX::SimpleMath::Vector4;
		using Color = DirectX::SimpleMath::Color;

		explicit RenderList(class DX11* pRenderer) : pRenderer(pRenderer)
		{
			vertices.reserve(MaxVertices);
			batches.reserve(4096);
			text_buffer.reserve(4096);
			text_data.reserve(4096);
		}

		void Draw() const noexcept;
		void DrawLine(Vector2 from, Vector2 to, Color const& color) noexcept;
		void DrawDot(Vector2 pos, Color const& color) noexcept;
		void DrawFilledRect(Vector4 const& rect, Color const& color) noexcept;
		void DrawRect(Vector4 const& rect, float strokeWidth, Color const& color) noexcept;
		void DrawOutlinedFilledRect(Vector4 const& rect, float strokeWidth, Color const& OutlineColor, Color const& color) noexcept;
		void DrawFilledRectGradient(Vector4 const& rect, Color color, float gradientIntensity = 1.f) noexcept;
		void DrawOutlinedRect(Vector4 const& rect, float strokeWidth, Color const& OutlineColor) noexcept;
		void DrawRect(Vector4 const& rect, Color const& InsideColor, Color const& OutlineColor) noexcept;
		void DrawRect(Vector4 const& rect, float strokeWidth, Color const& InsideColor, Color const& OutlineColor) noexcept;
		void DrawOutlinedString(const char* string, Vector2 pos, Color color, float scale) noexcept;
		void DrawCircle(Vector2 pos, float radius, Color const& color) noexcept;

		template <int smoothness>
		void DrawSmoothCircle(Vector2 pos, float radius, Color const& color) noexcept;

		void Draw2DText() const noexcept;
		void DrawString(const char* string, Vector2 pos, Color color, float scale) noexcept;
		Vector2 MeasureString(const char* string, bool ignore_whitespace = true) const noexcept;

		void Clear()
		{
			vertices.clear();
			batches.clear();

			if (!text_buffer.empty())
				text_buffer.clear();

			if (!text_data.empty())
				text_data.clear();

		}

		void ClampBuffer()
		{
			if (vertices.size() > MaxVertices)
				vertices.resize(MaxVertices);
		}

		static constexpr std::size_t MaxVertices = 65536 - 1000;
		std::vector<Vertex> vertices;
		std::vector<Batch>  batches;

		std::vector<std::pair<std::string, Vector2>> text_buffer;
		std::vector<std::pair<Color, float>> text_data;

	private:
		class DX11* pRenderer;
	};

	class TextureManager final
	{
	public:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Color = DirectX::SimpleMath::Color;

		explicit TextureManager(class DX11* pRenderer) : pRenderer(pRenderer)
		{
			textures.reserve(MaxTextureCount);
			texture_draw_data.reserve(MaxTextureCount);
		}

		void ClampTextureBuffer() noexcept;
		void ClearAllTextures() noexcept;

		void OnResize() noexcept;

		//Returns a texture id which will then be used to make a draw call to identify which texture is to be drawn
		int AddTexture(const wchar_t* file) noexcept;
		int AddTexture(const char* file) noexcept;
		int AddTexture(const uint8_t* memory, std::size_t size) noexcept;

		void DrawTexture(Vector2 pos, Color color, int texture_id, Vector2 scale = { 1.f, 1.f });
		void DrawTexture(Vector2 pos, int texture_id, Color color = { 1, 1, 1, 1 }, Vector2 scale = { 1.f, 1.f });
		Vector2 GetTextureSize(int texture_id) noexcept;

		//Do not fucking call this, it is meant to be called by my renderer
		void DrawTexture() noexcept;

		void Clear() noexcept;

	public:
		TextureManager(TextureManager const&) = delete;
		TextureManager& operator=(TextureManager const&) = delete;

		TextureManager(TextureManager&&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;

		~TextureManager() = default;

	private:
		//This is not being reset each frame, it is meant to be a one time Initialization
		struct TextureData
		{
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureResourceView;
			Microsoft::WRL::ComPtr<ID3D11Resource> pTextureResource;
			std::size_t buffer_size = 0; //Only used for memory textures
		};

		std::unordered_map<int, TextureData> textures;
		std::unordered_map<int, std::wstring> texture_file_map;
		std::unordered_map<int, void const*> memory_texture_file_map;

	private:
		//Texture information for each frame <- cleared every frame
		struct TextureDrawData
		{
			Vector2 pos;
			Vector2 texture_scaling;
			Color color;
			int texture_id;
		};

		std::vector<TextureDrawData> texture_draw_data;

	private:
		static constexpr std::size_t MaxTextureCount = 100;
		static inline int internal_texture_id = 0;
		class DX11* pRenderer;
	};

	class AudioManager
	{
	public:
		explicit AudioManager(class DX11* pRenderer) : pRenderer(pRenderer) { }
		bool InitializeAudioManager();
		int AddSoundEffect(const wchar_t* wavFile);
		int AddSoundEffect(const uint8_t* buffer, std::size_t size);
		void PlaySoundEffect(int soundID, float volume = 1.f, float pitch = 0.f, float pan = 0.f);

	public:
		AudioManager(AudioManager const&) = delete;
		AudioManager& operator=(AudioManager const&) = delete;

		AudioManager(AudioManager&&) = delete;
		AudioManager& operator=(AudioManager&&) = delete;

		~AudioManager() = default;

	private:
		struct SoundData
		{
			std::unique_ptr<DirectX::SoundEffect> pSoundEffect = nullptr;
			WAVEFORMATEX wavFormat{};
			std::wstring wav_file;
			void const* wavData = nullptr;
			std::size_t audio_size = 0;
		};

		//Currently has no real usage. It is just meant to store the sound infos in case we need them internally
		std::unordered_map<int, SoundData> sound_effects;

	private:
		static constexpr std::size_t MaxAudioCount = 10;
		static inline int internal_audio_id = 0;

	private:
		class DX11* pRenderer = nullptr;
		std::unique_ptr<DirectX::AudioEngine> pAudioEngine = nullptr;
	};

	//Pasted from the legendary Dear ImGui https://github.com/ocornut/imgui/blob/87f3109c1af835be0e5b4b4410baa1c66ced7b33/backends/imgui_impl_dx11.cpp#L205
	struct BACKUP_DX11_STATE
	{
		UINT                        ScissorRectsCount, ViewportsCount;
		D3D11_RECT                  ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		D3D11_VIEWPORT              Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		ID3D11RasterizerState*		RS;
		ID3D11BlendState*			BlendState;
		FLOAT                       BlendFactor[4];
		UINT                        SampleMask;
		UINT                        StencilRef;
		ID3D11DepthStencilState*	DepthStencilState;
		ID3D11ShaderResourceView*	PSShaderResource;
		ID3D11SamplerState*			PSSampler;
		ID3D11PixelShader*			PS;
		ID3D11VertexShader*			VS;
		ID3D11GeometryShader*		GS;
		UINT                        PSInstancesCount, VSInstancesCount, GSInstancesCount;
		ID3D11ClassInstance*		PSInstances[256], * VSInstances[256], * GSInstances[256];  
		D3D11_PRIMITIVE_TOPOLOGY    PrimitiveTopology;
		ID3D11Buffer*				IndexBuffer, * VertexBuffer, * VSConstantBuffer;
		UINT                        IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
		DXGI_FORMAT                 IndexBufferFormat;
		ID3D11InputLayout*			InputLayout;
	};

	class DX11
	{
		friend struct RenderList;
		friend struct ForegroundRenderList;
		friend class TextureManager;

	public:
		DX11(DX11 const&) = delete;
		DX11& operator=(DX11 const&) = delete;

		DX11(DX11&&) = delete;
		DX11& operator=(DX11&&) = delete;

	private:
		DX11() = default;
		virtual ~DX11() = default;

	public:
		static DX11* Get();
		static void AfterResize(IDXGISwapChain* pSwapChain) noexcept;
		static void BeforeResize() noexcept;

	public:
		bool Initialize(IDXGISwapChain* pSwapChain);
		void Begin();
		void End();

	public:
		RenderList* GetBackGroundRenderList() const noexcept;
		RenderList* GetForegroundRenderList() const noexcept;

		TextureManager* GetTextureRenderList() const noexcept;
		AudioManager* GetAudioManager() const noexcept;

	public:
		void ChangeFont(std::uint8_t* const pData, std::size_t size) noexcept;

	private:
		void AddVertices(RenderList* const pRenderList, std::span<Vertex> vertices, D3D11_PRIMITIVE_TOPOLOGY topology) const;

	private:
		bool InitializeDevices();
		bool InitializeBackBuffer();
		bool InitializePixelShader();
		bool InitializeVertexShader();
		bool InitializeVertexBuffer();
		bool InitializeRasterizerState();
		void InitializeFont();

	private:
		void SetConstantBuffer();
		void SetInputLayout();
		void SetBlendState();
		void SetCommonState();
		void SetWindowData();

	private:
		void CaptureDirectX11State() noexcept;
		void RestoreDirectX11State() const noexcept;

	private:
		ID3D11Device* pDevice;
		ID3D11DeviceContext* pDeviceContext;

		IDXGISwapChain* pSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;

		Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;
		Microsoft::WRL::ComPtr<ID3D11BlendState> pNonPremultipliedState = nullptr;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob> pVertexShaderBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> pPixelShaderBlob;


	private:
		DirectX::SimpleMath::Matrix projection_matrix;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantProjectionMatrixBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;

	private:
		std::unique_ptr<DirectX::SpriteBatch> spriteBatch = nullptr;
		std::unique_ptr<DirectX::SpriteFont> spriteFont = nullptr;
		std::unique_ptr<DirectX::CommonStates> common_states = nullptr;

	private:
		BACKUP_DX11_STATE previous_pipeline_state {};

	public:
		HWND windowHandle = nullptr;
		int windowWidth = 0;
		int windowHeight = 0;

	private:
		std::unique_ptr<RenderList> pBackGroundRenderList = std::make_unique<RenderList>(this);
		std::unique_ptr<RenderList> pForegroundRenderList = std::make_unique<RenderList>(this);

		std::unique_ptr<TextureManager> pTextureRenderList = std::make_unique<TextureManager>(this);
		std::unique_ptr<AudioManager> pAudioManager = std::make_unique<AudioManager>(this);
	};

	template <int smoothness>
	void RenderList::DrawSmoothCircle(Vector2 pos, float radius, Color const& color) noexcept
	{
		Vertex _vertices[smoothness + 1];

		float angleIncrement = DirectX::XM_2PI / smoothness;

		float x = radius, y = 0.0f;

		float cosTheta = std::cos(angleIncrement);
		float sinTheta = std::sin(angleIncrement);

		for (int i = 0; i <= smoothness; ++i) {

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

}