#pragma once

class ITexture;
class IReplayScreenshotSystem;
class WriteReplayScreenshotParams_t;
class CViewSetup;

class IViewRender
{
public:
	const Matrix4* GetWorldToScreenMatrix(bool bUnknown = false);
	bool HasWorldToScreenMatrix(bool bUnknown = false);
	virtual void		Init(void) = 0;
	virtual void		LevelInit(void) = 0;
	virtual void		LevelShutdown(void) = 0;
	virtual void		Shutdown(void) = 0;
	virtual void		OnRenderStart() = 0;
	virtual	void		Render(vrect_t* rect) = 0;
	virtual void		RenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
	virtual int GetDrawFlags() = 0;
	virtual void		StartPitchDrift(void) = 0;
	virtual void		StopPitchDrift(void) = 0;
	virtual /*VPlane*/void* GetFrustum() = 0;
	virtual bool		ShouldDrawBrushModels(void) = 0;
	virtual const CViewSetup* GetPlayerViewSetup(void) const = 0;
	virtual const CViewSetup* GetViewSetup(void) const = 0;
	virtual void		DisableVis(void) = 0;
	virtual int			BuildWorldListsNumber() const = 0;
	virtual void		SetCheapWaterStartDistance(float flCheapWaterStartDistance) = 0;
	virtual void		SetCheapWaterEndDistance(float flCheapWaterEndDistance) = 0;
	virtual void		GetWaterLODParams(float& flCheapWaterStartDistance, float& flCheapWaterEndDistance) = 0;
	virtual void		DriftPitch(void) = 0;
	virtual void		SetScreenOverlayMaterial(/*IMaterial*/void* pMaterial) = 0;
	virtual /*IMaterial*/void* GetScreenOverlayMaterial() = 0;
	virtual void		WriteSaveGameScreenshot(const char* pFilename) = 0;
	virtual void		WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height, bool bCreatePowerOf2Padded = false, bool bWriteVTF = false) = 0;
	virtual void		WriteReplayScreenshot(WriteReplayScreenshotParams_t& params) = 0;
	virtual void		UpdateReplayScreenshotCache() = 0;
	virtual void		QueueOverlayRenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
	virtual float		GetZNear() = 0;
	virtual float		GetZFar() = 0;
	virtual void		GetScreenFadeDistances(float* min, float* max) = 0;
	virtual C_BaseEntity* GetCurrentlyDrawingEntity() = 0;
	virtual void		SetCurrentlyDrawingEntity(C_BaseEntity* pEnt) = 0;
	virtual bool		UpdateShadowDepthTexture(ITexture* pRenderTarget, ITexture* pDepthTexture, const CViewSetup& shadowView) = 0;
	virtual void		FreezeFrame(float flFreezeTime) = 0;
	virtual IReplayScreenshotSystem* GetReplayScreenshotSystem() = 0;
};