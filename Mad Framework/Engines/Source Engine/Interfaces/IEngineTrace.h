#pragma once

#define	CONTENTS_EMPTY			0		// No contents
#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80
#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))
#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	
#define CONTENTS_UNUSED6		0x400
#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_AREAPORTAL		0x8000
#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000
#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity
#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace
#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture
#define	SURF_HINT		0x0100	// make a primary bsp splitter
#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface 
#define SURF_HITBOX		0x8000	// surface is part of a hitbox
#define CONTENTS_BULLETCLIP 0x400000
#define	MASK_ALL					(0xFFFFFFFF)
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)
#define TRACE_MASK_SHOT (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_SLIME|CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_BULLETCLIP|CONTENTS_MONSTER|CONTENTS_DEBRIS|CONTENTS_HITBOX)

class CTraceListData;
class IEntityEnumerator;
class ICollideable;

struct Ray_t {
	Vector4 start; // 0x0 (0xC)
	Vector4 delta; // 0x10 (0xC)
	Vector4 startOffset; // 0x20 (0xC)
	Vector4 extents; // 0x30 (0xC)
	void* axisWorldTransform; // 0x40 (0x8)
	int dword48; // 0x48 (0x4)
	bool isRay; // 0x4C (0x1)
	bool isSwept; // 0x4D (0x1)
	bool bool4E; // 0x4E (0x1)
	bool unk4; // 0x4F (0x1)
	int dword50; // 0x50 (0x4)

	void init(Vector3 _start, Vector3 _end)
	{
		this->delta = _end - _start;

		this->isSwept = (this->delta.Length() != 0);

		this->extents = Vector3{};

		this->isRay = true;

		this->startOffset = Vector3{};

		this->start = _start;
	}
};

struct Trace_t {
	Vector4 start; // 0x0 (0xC)
	Vector4 end; // 0x10 (0xC)
	Vector3 surfaceNormal; // 0x0 (0xC)
	float distance; // 0xC (0x4)
	float fraction; // 0x30 (0x4)
	int contents; // 0x34 (0x4)
	unsigned short dispFlags; // 0x38 (0x2)
	bool allSolid; // 0x3A (0x1)
	bool startSolid; // 0x3B (0x1)
	bool idk; // 0x3C (0x1)
	char pad1[0x3]; // 0x3D (0x3)
	float fractionLeftSolid; // 0x40 (0x4)
	char pad2[0x4]; // 0x44 (0x4)
	const char* surfaceName; // 0x48 (0x8)
	void* surfaceUnk; // 0x50 (0x8)
	int hitGroup; // 0x58 (0x4)
	short physicsBone; // 0x5C (0x2)
	unsigned short worldSurfaceIndex; // 0x5E (0x2)
	C_BaseEntity* entity; // 0x60 (0x8)
	int hitbox; // 0x68 (0x4)
	int dword6C; // 0x6C (0x4)
}; // 0x70

class IEngineTrace
{
public:
	virtual int		GetPointContents(const Vector3 & vecAbsPosition, IHandleEntity * *ppEntity = NULL) = 0;
	virtual int		GetPointContents_Collideable(ICollideable* pCollide, const Vector3& vecAbsPosition) = 0;
	virtual void	ClipRayToEntity(const Ray_t& ray, unsigned int fMask, IHandleEntity* pEnt, trace_t* pTrace) = 0;
	virtual void	ClipRayToCollideable(const Ray_t& ray, unsigned int fMask, ICollideable* pCollide, trace_t* pTrace) = 0;
	void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, Trace_t* pTrace) noexcept;
	virtual void	SetupLeafAndEntityListRay(const Ray_t& ray, CTraceListData& traceData) = 0;
	virtual void    SetupLeafAndEntityListBox(const Vector3& vecBoxMin, const Vector3& vecBoxMax, CTraceListData& traceData) = 0;
	virtual void	TraceRayAgainstLeafAndEntityList(const Ray_t& ray, CTraceListData& traceData, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void	EnumerateEntities(const Ray_t& ray, bool triggers, IEntityEnumerator* pEnumerator) = 0;
	virtual void	EnumerateEntities(const Vector3& vecAbsMins, const Vector3& vecAbsMaxs, IEntityEnumerator* pEnumerator) = 0;
};
