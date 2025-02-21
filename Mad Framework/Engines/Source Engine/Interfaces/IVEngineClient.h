#pragma once

class SurfInfo;
class CAudioSource;
class CSentence;
class ISpatialQuery;
class IMaterialSystem;
class IAchievementMgr;
class CGamestatsData;
class KeyValues;
struct client_textmessage_t;
class INetChannelInfo;
struct model_t;
struct color32;
class VMatrix;

typedef struct player_info_s
{
	char			name[32];
	int				userID;
	char			guid[32 + 1];
	unsigned __int32 friendsID;
	char			friendsName[32];
	bool			fakeplayer;
	bool			ishltv;
	bool			isreplay;
	unsigned int	customFiles[4];
	unsigned char	filesDownloaded;
	char pad[0x350];
} player_info_t;

struct AudioState_t
{
	Vector3 m_Origin;
	Vector3 m_Angles;
	bool m_bIsUnderwater;
};

enum SkyboxVisibility_t
{
	SKYBOX_NOT_VISIBLE = 0,
	SKYBOX_3DSKYBOX_VISIBLE,
	SKYBOX_2DSKYBOX_VISIBLE,
};

struct OcclusionParams_t
{
	float	m_flMaxOccludeeArea;
	float	m_flMinOccluderArea;
};

class IVEngineClient
{
public:
	virtual int					GetIntersectingSurfaces(
									const /*model_t*/void* model,
									const Vector3& vCenter,
									const float radius,
									const bool bOnlyVisibleSurfaces,	
									/*SurfInfo*/void * pInfos,
									const int nMaxInfos) = 0;
	virtual Vector3				GetLightForPoint(const Vector3& pos, bool bClamp) = 0;
	virtual /*IMaterial*/void* TraceLineMaterialAndLighting(const Vector3& start, const Vector3& end,
								Vector3& diffuseLightColor, Vector3& baseColor) = 0;
	virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
	virtual bool				CopyFile(const char* source, const char* destination) = 0;
	virtual void				GetScreenSize(int& width, int& height) = 0;
	virtual void				ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
	virtual void				ClientCmd(const char* szCmdString) = 0;
	bool						GetPlayerInfo(int ent_num, player_info_t* pinfo);
	virtual int					GetPlayerForUserID(int userID) = 0;
	virtual client_textmessage_t* TextMessageGet(const char* pName) = 0;
	virtual bool				Con_IsVisible(void) = 0;
	int							GetLocalPlayer(void);
	virtual const model_t* LoadModel(const char* pName, bool bProp = false) = 0;
	virtual float				Time(void) = 0;
	virtual float				GetLastTimeStamp(void) = 0;
	virtual CSentence* GetSentence(CAudioSource* pAudioSource) = 0;
	virtual float				GetSentenceLength(CAudioSource* pAudioSource) = 0;
	virtual bool				IsStreaming(CAudioSource* pAudioSource) const = 0;
	virtual void				GetViewAngles(QAngle& va) = 0;
	virtual void				SetViewAngles(QAngle& va) = 0;
	virtual int					GetMaxClients(void) = 0;
	virtual	const char* Key_LookupBinding(const char* pBinding) = 0;
	virtual const char* Key_BindingForKey(int& code) = 0;
	virtual void				StartKeyTrapMode(void) = 0;
	virtual bool				CheckDoneKeyTrapping(int& code) = 0;
	bool						IsInGame(void);
	virtual bool				IsConnected(void) = 0;
	virtual bool				IsDrawingLoadingImage(void) = 0;
	virtual void				Con_NPrintf(int pos, const char* fmt, ...) = 0;
	virtual void				Con_NXPrintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;
	virtual int					IsBoxVisible(const Vector3& mins, const Vector3& maxs) = 0;
	virtual int					IsBoxInViewCluster(const Vector3& mins, const Vector3& maxs) = 0;
	virtual bool				CullBox(const Vector3& mins, const Vector3& maxs) = 0;
	virtual void				Sound_ExtraUpdate(void) = 0;
	virtual const char* GetGameDirectory(void) = 0;
	virtual const VMatrix& WorldToScreenMatrix() = 0;
	virtual const VMatrix& WorldToViewMatrix() = 0;
	virtual int					GameLumpVersion(int lumpId) const = 0;
	virtual int					GameLumpSize(int lumpId) const = 0;
	virtual bool				LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
	virtual int					LevelLeafCount() const = 0;
	virtual ISpatialQuery* GetBSPTreeQuery() = 0;
	virtual void		LinearToGamma(float* linear, float* gamma) = 0;
	virtual float		LightStyleValue(int style) = 0;
	virtual int			GetDXSupportLevel() = 0;
	virtual bool        SupportsHDR() = 0;
	virtual void		Mat_Stub(IMaterialSystem* pMatSys) = 0;
	virtual void GetChapterName(char* pchBuff, int iMaxLength) = 0;
	virtual char const* GetLevelName(void) = 0;
	virtual void		EngineStats_BeginFrame(void) = 0;
	virtual void		EngineStats_EndFrame(void) = 0;
	virtual void		FireEvents() = 0;
	virtual int			GetLeavesArea(int* pLeaves, int nLeaves) = 0;
	virtual bool		DoesBoxTouchAreaFrustum(const Vector3& mins, const Vector3& maxs, int iArea) = 0;
	virtual void		SetAudioState(const AudioState_t& state) = 0;
	virtual int			SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
	virtual int			SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int			SentenceIndexFromName(const char* pSentenceName) = 0;
	virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int			SentenceGroupIndexFromName(const char* pGroupName) = 0;
	virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float		SentenceLength(int sentenceIndex) = 0;
	virtual void		ComputeLighting(const Vector3& pt, const Vector3* pNormal, bool bClamp, Vector3& color, Vector3* pBoxColors = NULL) = 0;
	virtual void		ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool		IsOccluded(const Vector3& vecAbsMins, const Vector3& vecAbsMaxs) = 0;
	virtual void* SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void		SaveFreeMemory(void* pSaveMem) = 0;
	virtual INetChannelInfo* GetNetChannelInfo(void) = 0;
	virtual void		DebugDrawPhysCollide(const /*CPhysCollide*/void* pCollide, /*IMaterial*/void* pMaterial, matrix3x4_t& transform, const color32& color) = 0;
	virtual void		CheckPoint(const char* pName) = 0;
	virtual void		DrawPortals() = 0;
	virtual bool		IsPlayingDemo(void) = 0;
	virtual bool		IsRecordingDemo(void) = 0;
	virtual bool		IsPlayingTimeDemo(void) = 0;
	virtual bool		IsPaused(void) = 0;
	virtual bool		IsTakingScreenshot(void) = 0;
	virtual bool		IsHLTV(void) = 0;
	virtual bool		IsLevelMainMenuBackground(void) = 0;
	virtual void		GetMainMenuBackgroundName(char* dest, int destlen) = 0;
	virtual void		SetOcclusionParameters(const OcclusionParams_t& params) = 0;
	virtual void		GetUILanguage(char* dest, int destlen) = 0;
	virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint(const Vector3& vecPoint) = 0;
	virtual const char* GetMapEntitiesString() = 0;
	virtual bool		IsInEditMode(void) = 0;
	virtual float		GetScreenAspectRatio() = 0;
	virtual bool		REMOVED_SteamRefreshLogin(const char* password, bool isSecure) = 0;
	virtual bool		REMOVED_SteamProcessCall(bool& finished) = 0;
	virtual unsigned int	GetEngineBuildNumber() = 0; 
	virtual const char* GetProductVersionString() = 0; 
	virtual void			GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
	virtual bool			IsHammerRunning() const = 0;
	virtual void			ExecuteClientCmd(const char* szCmdString) = 0;
	virtual bool MapHasHDRLighting(void) = 0;
	virtual int	GetAppID() = 0;
	virtual Vector3			GetLightForPointFast(const Vector3& pos, bool bClamp) = 0;
	virtual void			ClientCmd_Unrestricted(const char* szCmdString) = 0;
	virtual void			SetRestrictServerCommands(bool bRestrict) = 0;
	virtual void			SetRestrictClientCommands(bool bRestrict) = 0;
	virtual void			SetOverlayBindProxy(int iOverlayID, void* pBindProxy) = 0;
	virtual bool			CopyFrameBufferToMaterial(const char* pMaterialName) = 0;
	virtual void			ChangeTeam(const char* pTeamName) = 0;
	virtual void			ReadConfiguration(const bool readDefault = false) = 0;
	virtual void SetAchievementMgr(IAchievementMgr* pAchievementMgr) = 0;
	virtual IAchievementMgr* GetAchievementMgr() = 0;
	virtual bool			MapLoadFailed(void) = 0;
	virtual void			SetMapLoadFailed(bool bState) = 0;
	virtual bool			IsLowViolence() = 0;
	virtual const char* GetMostRecentSaveGame(void) = 0;
	virtual void			SetMostRecentSaveGame(const char* lpszFilename) = 0;
	virtual void			StartXboxExitingProcess() = 0;
	virtual bool			IsSaveInProgress() = 0;
	virtual unsigned int			OnStorageDeviceAttached(void) = 0;
	virtual void			OnStorageDeviceDetached(void) = 0;
	virtual void			ResetDemoInterpolation(void) = 0;
	virtual void SetGamestatsData(CGamestatsData* pGamestatsData) = 0;
	virtual CGamestatsData* GetGamestatsData() = 0;
	virtual bool IsPlayingDemoALocallyRecordedDemo() = 0;
};
