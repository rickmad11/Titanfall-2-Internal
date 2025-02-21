#pragma once

#include "Engines/Source Engine/Interfaces/IViewRender.h"
class CViewSetup;

class CViewRender : public IViewRender
{
public:
	virtual void						Init(void);
	virtual void						Shutdown(void);
	virtual void						StartPitchDrift(void);
	virtual void						StopPitchDrift(void);
	virtual float						GetZNear();
	virtual float						GetZFar();
	virtual void						OnRenderStart();
	virtual void						WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height, bool bCreatePowerOf2Padded = false, bool bWriteVTF = false);
	virtual void						WriteReplayScreenshot(WriteReplayScreenshotParams_t& params);
	virtual void						UpdateReplayScreenshotCache();
	virtual	void						Render(vrect_t* rect);
	virtual void						RenderView(const CViewSetup& view, int nClearFlags, int whatToDraw);
	virtual void						RenderPlayerSprites();
	virtual void						Render2DEffectsPreHUD(const CViewSetup& view);
	virtual void						Render2DEffectsPostHUD(const CViewSetup& view);
	virtual void						QueueOverlayRenderView(const CViewSetup& view, int nClearFlags, int whatToDraw);
	virtual void						GetScreenFadeDistances(float* min, float* max);
	virtual C_BaseEntity*				GetCurrentlyDrawingEntity();
	virtual void						SetCurrentlyDrawingEntity(C_BaseEntity* pEnt);
};