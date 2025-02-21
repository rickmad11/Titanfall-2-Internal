#include "pch.h"

#include "MiscVisuals.h"
#include "crosshairRawData.h"

void DrawCrosshair(int crosshair_variant, float size)
{
	static MadRenderer::DX11* pRenderer = MadRenderer::DX11::Get();
	MadRenderer::TextureManager* pTextureManager = pRenderer->GetTextureRenderList();

	static const auto s_TextureIDs = [pTextureManager]() -> const std::array<int, 3>
		{
			std::array<int, 3> temp_texture_array;
			temp_texture_array[0] = pTextureManager->AddTexture(crosshairVariant1, sizeof(crosshairVariant1));
			temp_texture_array[1] = pTextureManager->AddTexture(crosshairVariant2, sizeof(crosshairVariant2));
			temp_texture_array[2] = pTextureManager->AddTexture(crosshairVariant3, sizeof(crosshairVariant3));
			return temp_texture_array;
		}();

	const int texture_id = s_TextureIDs.at(crosshair_variant);

	auto [texture_width, texture_height] = pTextureManager->GetTextureSize(texture_id);

	pTextureManager->DrawTexture({ (pRenderer->windowWidth * 0.5f) - texture_width * size, (pRenderer->windowHeight * 0.5f) - texture_height * size }, texture_id,
		{1,1,1,1}, { size ,size });
}
