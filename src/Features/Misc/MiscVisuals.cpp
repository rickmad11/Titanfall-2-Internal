#include "pch.h"

#include "MiscVisuals.h"
#include "crosshairRawData.h"

void DrawCrosshair(int crosshair_variant, float size)
{
	static MadRenderer::DX11* pRenderer = MadRenderer::DX11::Get();
	MadRenderer::TextureManager* pTextureManager = pRenderer->GetTextureRenderList();

	static const std::array s_TextureIDs = 
	{
		pTextureManager->AddTexture(crosshairVariant1, sizeof(crosshairVariant1)),
		pTextureManager->AddTexture(crosshairVariant2, sizeof(crosshairVariant2)),
		pTextureManager->AddTexture(crosshairVariant3, sizeof(crosshairVariant3))
	};

	const int texture_id = s_TextureIDs.at(crosshair_variant);

	auto [texture_width, texture_height] = pTextureManager->GetTextureSize(texture_id);

	pTextureManager->DrawTexture({ (static_cast<float>(pRenderer->windowWidth) * 0.5f) - texture_width * size, (static_cast<float>(pRenderer->windowHeight) * 0.5f) - texture_height * size }, texture_id,
		{1,1,1,1}, { size ,size });
}
