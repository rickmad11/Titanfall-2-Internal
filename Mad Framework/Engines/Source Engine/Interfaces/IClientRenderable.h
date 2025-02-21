#pragma once

class IClientUnknown;
struct Vector3;
class QAngle;
struct matrix3x4_t;

class IClientRenderable
{
public:
	virtual IClientUnknown *		GetIClientUnknown() = 0;
	virtual Vector3 const&			GetRenderOrigin(void) = 0;
	virtual QAngle const&			GetRenderAngles(void) = 0;
	virtual bool					ShouldDraw(void) = 0;
	virtual bool					IsTransparent(void) = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual unsigned short			GetShadowHandle() const = 0;
	virtual unsigned short&			RenderHandle() = 0;
	virtual const /*model_t*/void*	GetModel() const = 0;
	virtual int						DrawModel(int flags) = 0;
	virtual int						GetBody() = 0;
	virtual void					ComputeFxBlend() = 0;
	virtual int						GetFxBlend(void) = 0;
	virtual void					GetColorModulation(float* color) = 0;
	virtual bool					LODTest() = 0;
	bool							SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	virtual void					SetupWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void					DoAnimationEvents(void) = 0;
	virtual							/*IPVSNotify*/void* GetPVSNotifyInterface() = 0;
	virtual void					GetRenderBounds(Vector3& mins, Vector3& maxs) = 0;
	virtual void					GetRenderBoundsWorldspace(Vector3& mins, Vector3& maxs) = 0;
	virtual void					GetShadowRenderBounds(Vector3& mins, Vector3& maxs, int shadowType) = 0;
	virtual bool					ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool					GetShadowCastDistance(float* pDist, int shadowType) const = 0;
	virtual bool					GetShadowCastDirection(Vector3* pDirection, int shadowType) const = 0;
	virtual bool					IsShadowDirty() = 0;
	virtual void					MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*		GetShadowParent() = 0;
	virtual IClientRenderable*		FirstShadowChild() = 0;
	virtual IClientRenderable*		NextShadowPeer() = 0;
	virtual int						ShadowCastType() = 0;
	virtual void					CreateModelInstance() = 0;
	virtual unsigned short			GetModelInstance() = 0;
	virtual const matrix3x4_t&		RenderableToWorldTransform() = 0;
	virtual int						LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool					GetAttachment(int number, Vector3& origin, QAngle& angles) = 0;
	virtual bool					GetAttachment(int number, matrix3x4_t& matrix) = 0;
	virtual float*					GetRenderClipPlane(void) = 0;
	virtual int						GetSkin() = 0;
	virtual bool					IsTwoPass(void) = 0;
	virtual void					OnThreadedDrawSetup() = 0;
	virtual bool					UsesFlexDelayedWeights() = 0;
	virtual void					RecordToolMessage() = 0;
};
