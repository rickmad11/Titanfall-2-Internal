#pragma once

class CGlobalVarsBase;
class bf_write;
struct vrect_t;
class CViewSetup;
struct ScreenFade_t;
class CEngineSprite;
class CSaveRestoreData;
struct datamap_t;
struct typedescription_t;
class CStandardRecvProxies;

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
typedef void* (*InstantiateInterfaceFn)();

class IBaseClientDLL
{
public:
	// Called once when the client DLL is loaded
	virtual int				Init(CreateInterfaceFn appSystemFactory,
									CreateInterfaceFn physicsFactory,
									CGlobalVarsBase * pGlobals) = 0;
	virtual void			PostInit() = 0;
	virtual void			Shutdown(void) = 0;
	virtual void			LevelInitPreEntity(char const* pMapName) = 0;
	virtual void			LevelInitPostEntity() = 0;
	virtual void			LevelShutdown(void) = 0;
	ClientClass*			GetAllClasses(void);
	virtual int				HudVidInit(void) = 0;
	virtual void			HudProcessInput(bool bActive) = 0;
	virtual void			HudUpdate(bool bActive) = 0;
	virtual void			HudReset(void) = 0;
	virtual void			HudText(const char* message) = 0;
	virtual void			IN_ActivateMouse(void) = 0;
	virtual void			IN_DeactivateMouse(void) = 0;
	virtual void			IN_Accumulate(void) = 0;
	virtual void			IN_ClearStates(void) = 0;
	virtual bool			IN_IsKeyDown(const char* name, bool& isdown) = 0;
	virtual int				IN_KeyEvent(int eventcode, int keynum, const char* pszCurrentBinding) = 0;
	virtual void			CreateMove(
								int sequence_number,			
								float input_sample_frametime,	
								bool active) = 0;				
	virtual void			ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool			WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isnewcommand) = 0;
	virtual void			EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
	virtual void			DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;
	virtual void			View_Render(vrect_t* rect) = 0;
	virtual void			RenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
	virtual void			View_Fade(ScreenFade_t* pSF) = 0;
	virtual void			SetCrosshairAngle(const QAngle& angle) = 0;
	virtual void			InitSprite(CEngineSprite* pSprite, const char* loadname) = 0;
	virtual void			ShutdownSprite(CEngineSprite* pSprite) = 0;
	virtual int				GetSpriteSize(void) const = 0;
	virtual void			VoiceStatus(int entindex, int bTalking) = 0;
	virtual void			InstallStringTableCallback(char const* tableName) = 0;
	virtual void			FrameStageNotify(int curStage) = 0;
	virtual bool			DispatchUserMessage(int msg_type, bf_read& msg_data) = 0;
	virtual CSaveRestoreData* SaveInit(int size) = 0;
	virtual void			SaveWriteFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void			SaveReadFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void			PreSave(CSaveRestoreData*) = 0;
	virtual void			Save(CSaveRestoreData*) = 0;
	virtual void			WriteSaveHeaders(CSaveRestoreData*) = 0;
	virtual void			ReadRestoreHeaders(CSaveRestoreData*) = 0;
	virtual void			Restore(CSaveRestoreData*, bool) = 0;
	virtual void			DispatchOnRestore() = 0;
	virtual CStandardRecvProxies* GetStandardRecvProxies() = 0;
	virtual void			WriteSaveGameScreenshot(const char* pFilename) = 0;
	virtual void			EmitSentenceCloseCaption(char const* tokenstream) = 0;
	virtual void			EmitCloseCaption(char const* captionname, float duration) = 0;
	virtual bool			CanRecordDemo(char* errorMsg, int length) const = 0;
	virtual void			WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height) = 0;
	virtual bool			GetPlayerView(CViewSetup& playerView) = 0;
	virtual unsigned int	GetPresenceID(const char* pIDName) = 0;
	virtual const char*		GetPropertyIdString(const unsigned int id) = 0;
	virtual void			GetPropertyDisplayString(unsigned int id, unsigned int value, char* pOutput, int nBytes) = 0;
#ifdef _WIN32
	virtual void			StartStatsReporting(HANDLE handle, bool bArbitrated) = 0;
#endif
	virtual void			InvalidateMdlCache() = 0;
	virtual void			IN_SetSampleTime(float frametime) = 0;
};
