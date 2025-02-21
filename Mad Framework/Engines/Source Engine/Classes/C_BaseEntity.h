#pragma once

#include "../Interfaces/IClientEntity.h"
#include "Engines/Source Engine/NetVarManager/NetVarManager.h"

class CTakeDamageInfo;
class ITraceFilter;
class CDmgAccumulator;
class CEntityMapData;
class C_BaseAnimating;
class ISave;
class IRestore;
class IPhysicsObject;
class C_Team;
class CNewParticleEffect;
class IClientVehicle;
class CStudioHdr;
class CDamageModifier;
class C_BaseCombatCharacter;
class C_BaseCombatWeapon;
struct EmitSound_t;
struct CollideType_t;
struct Ray_t;
struct trace_t;
struct FireBulletsInfo_t;
class Quaternion;
class KeyValues;

enum thinkmethods_t
{
	THINK_FIRE_ALL_FUNCTIONS,
	THINK_FIRE_BASE_ONLY,
	THINK_FIRE_ALL_BUT_BASE,
};

class C_BaseEntity : public IClientEntity
{
public:
	virtual                         ~C_BaseEntity() = 0;

	virtual /*datamap_t*/void* GetDataDescMap() = 0;
	virtual void* YouForgotToImplementOrDeclareClientClass() = 0;
	virtual /*datamap_t*/void* GetPredDescMap() = 0;

	virtual void					FireBullets(const FireBulletsInfo_t& info) = 0;
	virtual void					ModifyFireBulletsDamage(CTakeDamageInfo* dmgInfo) = 0;
	virtual bool					ShouldDrawUnderwaterBulletBubbles() = 0;
	virtual bool					ShouldDrawWaterImpacts(void) = 0;
	virtual bool					HandleShotImpactingWater(const FireBulletsInfo_t& info, const Vector3& vecEnd, ITraceFilter* pTraceFilter, Vector3* pVecTracerDest) = 0;
	virtual ITraceFilter* GetBeamTraceFilter(void) = 0;
	virtual void					DispatchTraceAttack(const CTakeDamageInfo* info, const Vector3& vecDir, trace_t* ptr, CDmgAccumulator* pAccumulator = NULL) = 0;
	virtual void					TraceAttack(const CTakeDamageInfo* info, const Vector3& vecDir, trace_t* ptr, CDmgAccumulator* pAccumulator = NULL) = 0;
	virtual void					DoImpactEffect(trace_t& tr, int nDamageType) = 0;
	virtual void					MakeTracer(const Vector3& vecTracerSrc, const trace_t& tr, int iTracerType) = 0;
	virtual int						GetTracerAttachment(void) = 0;
	virtual int						BloodColor() = 0;
	virtual const char* GetTracerType() = 0;
	virtual void					Spawn(void) = 0;
	virtual void					SpawnClientEntity(void) = 0;
	virtual void					Precache(void) = 0;
	virtual void					Activate() = 0;
	virtual void					ParseMapData(CEntityMapData* mapData) = 0;
	virtual bool					KeyValue(const char* szKeyName, const char* szValue) = 0;
	virtual bool					KeyValue(const char* szKeyName, float flValue) = 0;
	virtual bool					KeyValue(const char* szKeyName, const Vector3& vecValue) = 0;
	virtual bool					GetKeyValue(const char* szKeyName, char* szValue, int iMaxLen) = 0;
	virtual bool					Init(int entnum, int iSerialNum) = 0;
	virtual C_BaseAnimating* GetBaseAnimating() = 0;
	virtual void					SetClassname(const char* className) = 0;
	virtual void			        RecordToolMessage() = 0;
	virtual Vector3					GetObserverCamOrigin(void) = 0;
	virtual bool					TestCollision(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual bool					TestHitboxes(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual float					GetAttackDamageScale(void) = 0;
	virtual void					ValidateModelIndex(void) = 0;
	virtual void					SetDormant(bool bDormant) = 0;
	virtual int				        GetEFlags() const = 0;
	virtual void			        SetEFlags(int iEFlags) = 0;
	virtual bool					ShouldSavePhysics() = 0;
	virtual void					OnSave() = 0;
	virtual void					OnRestore() = 0;
	virtual int						ObjectCaps(void) = 0;
	virtual int						Save(ISave& save) = 0;
	virtual int						Restore(IRestore& restore) = 0;
	virtual bool	                CreateVPhysics() = 0;
	virtual void	                VPhysicsDestroyObject(void) = 0;
	virtual void					VPhysicsUpdate(IPhysicsObject* pPhysics) = 0;
	virtual int						VPhysicsGetObjectList(IPhysicsObject** pList, int listMax) = 0;
	virtual bool					VPhysicsIsFlesh(void) = 0;
	virtual void					AddEntity(void) = 0;
	virtual const Vector3& GetPrevLocalOrigin() const = 0;
	virtual const Vector3& GetPrevLocalAngles() const = 0;
	virtual int						CalcOverrideModelIndex() = 0;
	virtual const Vector3& WorldAlignMins() const = 0;
	virtual const Vector3& WorldAlignMaxs() const = 0;
	virtual const Vector3& WorldSpaceCenter() const = 0;
	virtual void					ComputeWorldSpaceSurroundingBox(Vector3* pVecWorldMins, Vector3* pVecWorldMaxs) = 0;
	virtual float					GetHealthBarHeightOffset() const = 0;
	virtual int						GetSolid(void) const = 0;
	virtual int			 			GetSolidFlags(void) const = 0;
	virtual bool					GetAttachment(int number, Vector3& origin) = 0;
	virtual bool					GetAttachmentVelocity(int number, Vector3& originVel, Quaternion& angleVel) = 0;
	virtual C_Team* GetTeam(void) const = 0;
	virtual int						GetTeamNumber(void) const = 0;
	virtual void					ChangeTeam(int iTeamNum) = 0;
	virtual int						GetRenderTeamNumber(void) = 0;
	virtual bool					InSameTeam(const C_BaseEntity* pEntity) const = 0;
	virtual bool					InLocalTeam(void) = 0;
	virtual bool					IsValidIDTarget(void) = 0;
	virtual const char* GetIDString(void) = 0;
	virtual void                    ModifyEmitSoundParams(EmitSound_t& params) = 0;
	virtual bool                    InitializeAsClientEntity(const char* pszModelName, int renderGroup) = 0; //RenderGroup_t
	virtual void					Simulate() = 0;
	virtual IClientVehicle* GetClientVehicle() = 0;
	virtual void					GetAimEntOrigin(IClientEntity* pAttachedTo, Vector3* pAbsOrigin, Vector3* pAbsAngles) = 0;
	virtual const Vector3& GetOldOrigin() = 0;
	virtual int			            GetRenderGroup() = 0; //RenderGroup_t
	virtual void					GetToolRecordingState(KeyValues* msg) = 0;
	virtual void					CleanupToolRecordingState(KeyValues* msg) = 0;
	virtual CollideType_t			GetCollideType(void) = 0;
	virtual void					UpdateVisibility() = 0;
	virtual bool					IsSelfAnimating() = 0;
	virtual	void					OnLatchInterpolatedVariables(int flags) = 0;
	virtual CStudioHdr* OnNewModel() = 0;
	virtual void					OnNewParticleEffect(const char* pszParticleName, CNewParticleEffect* pNewParticleEffect) = 0;
	virtual void					ResetLatched() = 0;
	virtual bool					Interpolate(float currentTime) = 0;
	virtual bool					IsSubModel(void) = 0;
	virtual void					CreateLightEffects(void) = 0;
	virtual void					Clear(void) = 0;
	virtual int						DrawBrushModel(bool bTranslucent, int nFlags, bool bTwoPass) = 0;
	virtual float					GetTextureAnimationStartTime() = 0;
	virtual void					TextureAnimationWrapped() = 0;
	virtual void					SetNextClientThink(float nextThinkTime) = 0;
	virtual void					SetHealth(int iHealth) = 0;
	virtual int						GetHealth() const = 0;
	virtual int						GetMaxHealth() const = 0;
	virtual bool					IsVisibleToTargetID(void) const = 0;
	virtual bool					IsHealthBarVisible(void) const = 0;
	virtual int						ShadowCastType() = 0;
	virtual bool					ShouldReceiveProjectedTextures(int flags) = 0;
	virtual void					AddDecal(const Vector3& rayStart, const Vector3& rayEnd, const Vector3& decalCenter, int hitbox, int decalIndex, bool doTrace, trace_t& tr, int maxLODToDecal = -1) = 0;
	virtual void					AddColoredDecal(const Vector3& rayStart, const Vector3& rayEnd, const Vector3& decalCenter, int hitbox, int decalIndex, bool doTrace, trace_t& tr, Vector3 cColor, int maxLODToDecal = -1) = 0;
	virtual bool					IsClientCreated(void) const = 0;
	virtual void					UpdateOnRemove(void) = 0;
	virtual void					SUB_Remove(void) = 0;
	virtual void					SetPredictable(bool state) = 0;
	virtual int						RestoreData(const char* context, int slot, int type) = 0;
	virtual char const* DamageDecal(int bitsDamageType, int gameMaterial) = 0;
	virtual void					DecalTrace(trace_t* pTrace, char const* decalName) = 0;
	virtual void					ImpactTrace(trace_t* pTrace, int iDamageType, const char* pCustomImpactName) = 0;
	virtual bool					ShouldPredict(void) = 0;
	virtual void					Think(void) = 0;
	virtual bool			        CanBePoweredUp(void) = 0;
	virtual bool			        AttemptToPowerup(int iPowerup, float flTime, float flAmount = 0, C_BaseEntity* pAttacker = NULL, CDamageModifier* pDamageModifier = NULL) = 0;
	virtual bool			        IsCurrentlyTouching(void) const = 0;
	virtual void			        StartTouch(C_BaseEntity* pOther) = 0;
	virtual void			        Touch(C_BaseEntity* pOther) = 0;
	virtual void			        EndTouch(C_BaseEntity* pOther) = 0;
	virtual unsigned int	        PhysicsSolidMaskForEntity(void) const = 0;
	virtual void					PhysicsSimulate(void) = 0;
	virtual bool					IsAlive(void) = 0;
	virtual bool					IsBaseCombatCharacter(void) = 0;
	virtual C_BaseCombatCharacter* MyCombatCharacterPointer(void) = 0;
	virtual bool					IsNPC(void) = 0;
	virtual bool					IsNextBot() = 0;
	virtual bool					IsBaseObject(void) const = 0;
	virtual bool					IsBaseCombatWeapon(void) const = 0;
	virtual C_BaseCombatWeapon* MyCombatWeaponPointer() = 0;
	virtual bool					IsCombatItem(void) const = 0;
	virtual bool					IsBaseTrain(void) const = 0;
	virtual Vector3			        EyePosition(void) = 0;
	virtual const Vector3& EyeAngles(void) = 0;
	virtual const Vector3& LocalEyeAngles(void) = 0;
	virtual Vector3		            EarPosition(void) = 0;
	virtual bool		            ShouldCollide(int collisionGroup, int contentsMask) const = 0;
	virtual const Vector3& GetViewOffset() const = 0;
	virtual void		            SetViewOffset(const Vector3& v) = 0;
	virtual void                    ClientAdjustStartSoundParams(void* unk) = 0; //EmitSound_t
	virtual void                    ClientAdjustStartSoundParams2(void* unk) = 0; //StartSoundParams_t
	virtual bool                    ShouldInterpolate() = 0;
	virtual unsigned char           GetClientSideFade() = 0;
	virtual void                    BoneMergeFastCullBloat(Vector3& localMins, Vector3& localMaxs, const Vector3& thisEntityMins, const Vector3& thisEntityMaxs) const = 0;
	virtual bool					OnPredictedEntityRemove(bool isbeingremoved, C_BaseEntity* predicted) = 0;
	virtual C_BaseEntity* GetShadowUseOtherEntity(void) const = 0;
	virtual void					SetShadowUseOtherEntity(C_BaseEntity* pEntity) = 0;
	virtual bool					AddRagdollToFadeQueue(void) = 0;
	virtual bool					IsDeflectable() = 0;
	virtual int						GetStudioBody(void) = 0;
	virtual void                    PerformCustomPhysics(Vector3* pNewPosition, Vector3* pNewVelocity, Vector3* pNewAngles, Vector3* pNewAngVelocity) = 0;
	virtual bool                    ValidateEntityAttachedToPlayer(bool& bShouldRetry) = 0;
	class CWeapon* GetActiveWeapon() noexcept;
	bool IsTitan() noexcept;
	bool IsPlayer() noexcept;

public:
	NETVAR(GetTeamNum, int, "CPlayer", "m_iTeamNum")
	NETVAR(GetHealth, int, "CPlayer", "m_iHealth")
	NETVAR(GetMaxHealth, int, "CPlayer", "m_iMaxHealth")
	NETVAR(GetSignifierName, const char*, "CPlayer", "m_iSignifierName")
	NETVAR(GetLifeState, int, "CPlayer", "m_lifeState")
	NETVAR(IsZooming, bool, "CPlayer", "m_bZooming")
	NETVAR_OFFSET(GetLocalOrigin, Vector3, 0x12C)
	NETVAR_OFFSET(GetCameraPos, Vector3, 0x19A4)
	NETVAR_OFFSET(GetWeaponSway, Vector3, 0x1E34)
};