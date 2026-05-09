#pragma once

typedef unsigned short MDLHandle_t;

enum MDLCacheDataType_t
{
    // Callbacks to get called when data is loaded or unloaded for these:
    MDLCACHE_STUDIOHDR = 0,
    MDLCACHE_STUDIOHWDATA,
    MDLCACHE_VCOLLIDE,

    // Callbacks NOT called when data is loaded or unloaded for these:
    MDLCACHE_ANIMBLOCK,
    MDLCACHE_VIRTUALMODEL,
    MDLCACHE_VERTEXES,
    MDLCACHE_DECODEDANIMBLOCK,
};

enum MDLCacheFlush_t
{
    MDLCACHE_FLUSH_STUDIOHDR = 0x01,
    MDLCACHE_FLUSH_STUDIOHWDATA = 0x02,
    MDLCACHE_FLUSH_VCOLLIDE = 0x04,
    MDLCACHE_FLUSH_ANIMBLOCK = 0x08,
    MDLCACHE_FLUSH_VIRTUALMODEL = 0x10,
    MDLCACHE_FLUSH_AUTOPLAY = 0x20,
    MDLCACHE_FLUSH_VERTEXES = 0x40,

    MDLCACHE_FLUSH_IGNORELOCK = 0x80000000,
    MDLCACHE_FLUSH_ALL = 0xFFFFFFFF
};

//https://developer.valvesoftware.com/wiki/MDL
struct studiohdr_t
{
    int         id;             // Model format ID, such as "IDST" (0x49 0x44 0x53 0x54)
    int         version;        // Format version number, such as 48 (0x30,0x00,0x00,0x00)
    int         checksum;       // This has to be the same in the phy and vtx files to load!
    int         unk;            //tf2 shit i dont fucking know
    char        name[64];       // The internal name of the model, padding with null bytes.
    // Typically "my_model.mdl" will have an internal name of "my_model"
    int         dataLength;     // Data size of MDL file in bytes.

    // A vector is 12 bytes, three 4-byte float-values in a row.
    Vector3      eyeposition;    // Position of player viewpoint relative to model origin
    Vector3      illumposition;  // Position (relative to model origin) used to calculate ambient light contribution and cubemap reflections for the entire model.
    Vector3      hull_min;       // Corner of model hull box with the least X/Y/Z values
    Vector3      hull_max;       // Opposite corner of model hull box
    Vector3      view_bbmin;     // Same, but for bounding box,
    Vector3      view_bbmax;     // which is used for view culling

    int         flags;          // Binary flags in little-endian order.
    // ex (0x010000C0) means flags for position 0, 30, and 31 are set.
    // Set model flags section for more information

/*
 * After this point, the header contains many references to offsets
 * within the MDL file and the number of items at those offsets.
 *
 * Offsets are from the very beginning of the file.
 *
 * Note that indexes/counts are not always paired and ordered consistently.
 */

 // mstudiobone_t
    int        bone_count;    // Number of data sections (of type mstudiobone_t)
    int        bone_offset;   // Offset of first data section

    // mstudiobonecontroller_t
    int        bonecontroller_count;
    int        bonecontroller_offset;

    // mstudiohitboxset_t
    int        hitbox_count;
    int        hitbox_offset;

    // mstudioanimdesc_t
    int        localanim_count;
    int        localanim_offset;

    // mstudioseqdesc_t
    int        localseq_count;
    int        localseq_offset;

    int        activitylistversion; // ??
    int        eventsindexed;       // ??

    // VMT texture filenames
    // mstudiotexture_t
    int        texture_count;
    int        texture_offset;

    // This offset points to a series of ints.
    // Each int value, in turn, is an offset relative to the start of this header/the-file,
    // At which there is a null-terminated string.
    int        texturedir_count;
    int        texturedir_offset;

    // Each skin-family assigns a texture-id to a skin location
    int        skinreference_count;
    int        skinrfamily_count;
    int        skinreference_index;

    // mstudiobodyparts_t
    int        bodypart_count;
    int        bodypart_offset;

    // Local attachment points
    // mstudioattachment_t
    int        attachment_count;
    int        attachment_offset;

    // Node values appear to be single bytes, while their names are null-terminated strings.
    int        localnode_count;
    int        localnode_index;
    int        localnode_name_index;

    // mstudioflexdesc_t
    int        flexdesc_count;
    int        flexdesc_index;

    // mstudioflexcontroller_t
    int        flexcontroller_count;
    int        flexcontroller_index;

    // mstudioflexrule_t
    int        flexrules_count;
    int        flexrules_index;

    // IK probably referse to inverse kinematics
    // mstudioikchain_t
    int        ikchain_count;
    int        ikchain_index;

    // Information about any "mouth" on the model for speech animation
    // More than one sounds pretty creepy.
    // mstudiomouth_t
    int        mouths_count;
    int        mouths_index;

    // mstudioposeparamdesc_t
    int        localposeparam_count;
    int        localposeparam_index;

    /*
     * For anyone trying to follow along, as of this writing,
     * the next "surfaceprop_index" value is at position 0x0134 (308)
     * from the start of the file.
     */

     // Surface property value (single null-terminated string)
    int        surfaceprop_index;

    // Unusual: In this one index comes first, then count.
    // Key-value data is a series of strings. If you can't find
    // what you're interested in, check the associated PHY file as well.
    int        keyvalue_index;
    int        keyvalue_count;

    // More inverse-kinematics
    // mstudioiklock_t
    int        iklock_count;
    int        iklock_index;


    float      mass;      // Mass of object (4-bytes) in kilograms

    int        contents;    // contents flag, as defined in bspflags.h
    // not all content types are valid; see
    // documentation on $contents QC command

// Other models can be referenced for re-used sequences and animations
// (See also: The $includemodel QC option.)
// mstudiomodelgroup_t
    int        includemodel_count;
    int        includemodel_index;

    int        virtualModel;    // Placeholder for mutable-void*
    // Note that the SDK only compiles as 32-bit, so an int and a pointer are the same size (4 bytes)

    // mstudioanimblock_t
    int        animblocks_name_index;
    int        animblocks_count;
    int        animblocks_index;

    int        animblockModel; // Placeholder for mutable-void*

    // Points to a series of bytes?
    int        bonetablename_index;

    int        vertex_base;    // Placeholder for void*
    int        offset_base;    // Placeholder for void*

    // Used with $constantdirectionallight from the QC 
    // Model should have flag #13 set if enabled
    byte        directionaldotproduct;

    byte        rootLod;    // Preferred rather than clamped

    // 0 means any allowed, N means Lod 0 -> (N-1)
    byte        numAllowedRootLods;

    byte        unused0; // ??
    int         unused1; // ??

    // mstudioflexcontrollerui_t
    int         flexcontrollerui_count;
    int         flexcontrollerui_index;

    float       vertAnimFixedPointScale; // ??
    int         unused2;

    /**
     * Offset for additional header information.
     * May be zero if not present, or also 408 if it immediately
     * follows this studiohdr_t
     */
     // studiohdr2_t
    int         studiohdr2index;

    int         unused3; // ??

    /**
     * As of this writing, the header is 408 bytes long in total
     */
};

struct studiomeshgroup_t
{
    void* m_pMesh;
    int				m_NumStrips;
    int				m_Flags;		// see studiomeshgroupflags_t
    void* m_pStripData;
    unsigned short* m_pGroupIndexToMeshIndex;
    int				m_NumVertices;
    int* m_pUniqueTris;	// for performance measurements
    unsigned short* m_pIndices;
    bool			m_MeshNeedsRestore;
    short			m_ColorMeshID;
    void* m_pMorph;

    inline unsigned short MeshIndex(int i) const { return m_pGroupIndexToMeshIndex[m_pIndices[i]]; }
};

struct studiomeshdata_t
{
    int					m_NumGroup;
    studiomeshgroup_t* m_pMeshGroup;
};

struct studioloddata_t
{
    // not needed - this is really the same as studiohwdata_t.m_NumStudioMeshes
    //int					m_NumMeshes; 
    studiomeshdata_t* m_pMeshData; // there are studiohwdata_t.m_NumStudioMeshes of these.
    float				m_SwitchPoint;
    // one of these for each lod since we can switch to simpler materials on lower lods.
    int					numMaterials;
    void** ppMaterials; /* will have studiohdr_t.numtextures elements allocated */
    // hack - this needs to go away.
    int* pMaterialFlags; /* will have studiohdr_t.numtextures elements allocated */

    // For decals on hardware morphing, we must actually do hardware skinning
    // For this to work, we have to hope that the total # of bones used by
    // hw flexed verts is < than the max possible for the dx level we're running under
    int* m_pHWMorphDecalBoneRemap;
    int					m_nDecalBoneCount;
};

struct studiohwdata_t
{
    int					m_RootLOD;	// calced and clamped, nonzero for lod culling
    int					m_NumLODs;
    studioloddata_t* m_pLODs;
    int					m_NumStudioMeshes;

    inline float LODMetric(float unitSphereSize) const { return (unitSphereSize != 0.0f) ? (100.0f / unitSphereSize) : 0.0f; }
    inline int GetLODForMetric(float lodMetric) const
    {
        if (!m_NumLODs)
            return 0;

        // shadow lod is specified on the last lod with a negative switch
        // never consider shadow lod as viable candidate
        int numLODs = (m_pLODs[m_NumLODs - 1].m_SwitchPoint < 0.0f) ? m_NumLODs - 1 : m_NumLODs;

        for (int i = m_RootLOD; i < numLODs - 1; i++)
        {
            if (m_pLODs[i + 1].m_SwitchPoint > lodMetric)
                return i;
        }

        return numLODs - 1;
    }
};

struct mstudiobone_t
{
    int					sznameindex;
    inline char* const pszName(void) const { return ((char*)this) + sznameindex; }
    int		 			parent;		// parent bone
    int					bonecontroller[6];	// bone controller index, -1 == none

    // default values
    Vector3				pos;
    Quaternion			quat;
    Vector3			rot;
    // compression scale
    Vector3				posscale;
    Vector3				rotscale;

    matrix3x4_t			poseToBone;
    Quaternion			qAlignment;
    int					flags;
    int					proctype;
    int					procindex;		// procedural rule
    mutable int			physicsbone;	// index into physically simulated bone
    inline void* pProcedure() const { if (procindex == 0) return NULL; else return  (void*)(((byte*)this) + procindex); };
    int					surfacepropidx;	// index into string tablefor property name
    inline char* const pszSurfaceProp(void) const { return ((char*)this) + surfacepropidx; }
    int					contents;		// See BSPFlags.h for the contents flags

    int					unused[15];		// remove as appropriate
};

struct CMDLCache // : public AppSystem
{
	// Used to install callbacks for when data is loaded + unloaded
// Returns the prior notify
	virtual void SetCacheNotify(void* pNotify) = 0;

	// NOTE: This assumes the "GAME" path if you don't use
	// the UNC method of specifying files. This will also increment
	// the reference count of the MDL
	MDLHandle_t FindMDL(const char* pMDLRelativePath);

	// Reference counting
	virtual int AddRef(MDLHandle_t handle) = 0;
	virtual int Release(MDLHandle_t handle) = 0;
	virtual int GetRef(MDLHandle_t handle) = 0;

	// Gets at the various data associated with a MDL
	virtual studiohdr_t* GetStudioHdr(MDLHandle_t handle) = 0;
	virtual studiohwdata_t* GetHardwareData(MDLHandle_t handle) = 0;
	virtual void* GetVCollide(MDLHandle_t handle) = 0;
	virtual unsigned char* GetAnimBlock(MDLHandle_t handle, int nBlock) = 0;
	virtual void* GetVirtualModel(MDLHandle_t handle) = 0;
	virtual int GetAutoplayList(MDLHandle_t handle, unsigned short** pOut) = 0;
	virtual void* GetVertexData(MDLHandle_t handle) = 0;

	// Brings all data associated with an MDL into memory
	virtual void TouchAllData(MDLHandle_t handle) = 0;

	// Gets/sets user data associated with the MDL
	virtual void SetUserData(MDLHandle_t handle, void* pData) = 0;
	virtual void* GetUserData(MDLHandle_t handle) = 0;

	// Is this MDL using the error model?
	virtual bool IsErrorModel(MDLHandle_t handle) = 0;

	// Flushes the cache, force a full discard
	virtual void Flush(MDLCacheFlush_t nFlushFlags = MDLCACHE_FLUSH_ALL) = 0;

	// Flushes a particular model out of memory
	virtual void Flush(MDLHandle_t handle, int nFlushFlags = MDLCACHE_FLUSH_ALL) = 0;

	// Returns the name of the model (its relative path)
	virtual const char* GetModelName(MDLHandle_t handle) = 0;

	// faster access when you already have the studiohdr
	virtual void* GetVirtualModelFast(const studiohdr_t* pStudioHdr, MDLHandle_t handle) = 0;

	// all cache entries that subsequently allocated or successfully checked 
	// are considered "locked" and will not be freed when additional memory is needed
	virtual void BeginLock() = 0;

	// reset all protected blocks to normal
	virtual void EndLock() = 0;

	// returns a pointer to a counter that is incremented every time the cache has been out of the locked state (EVIL)
	virtual int* GetFrameUnlockCounterPtrOLD() = 0;

	// Finish all pending async operations
	virtual void FinishPendingLoads() = 0;

	virtual void* GetVCollideEx(MDLHandle_t handle, bool synchronousLoad = true) = 0;
	virtual bool GetVCollideSize(MDLHandle_t handle, int* pVCollideSize) = 0;

	virtual bool GetAsyncLoad(MDLCacheDataType_t type) = 0;
	virtual bool SetAsyncLoad(MDLCacheDataType_t type, bool bAsync) = 0;

	virtual void BeginMapLoad() = 0;
	virtual void EndMapLoad() = 0;
	virtual void MarkAsLoaded(MDLHandle_t handle) = 0;

	virtual void InitPreloadData(bool rebuild) = 0;
	virtual void ShutdownPreloadData() = 0;

	virtual bool IsDataLoaded(MDLHandle_t handle, MDLCacheDataType_t type) = 0;

	virtual int* GetFrameUnlockCounterPtr(MDLCacheDataType_t type) = 0;

	virtual studiohdr_t* LockStudioHdr(MDLHandle_t handle) = 0;
	virtual void UnlockStudioHdr(MDLHandle_t handle) = 0;

	virtual bool PreloadModel(MDLHandle_t handle) = 0;

	// Hammer uses this. If a model has an error loading in GetStudioHdr, then it is flagged
	// as an error model and any further attempts to load it will just get the error model.
	// That is, until you call this function. Then it will load the correct model.
	virtual void ResetErrorModelStatus(MDLHandle_t handle) = 0;

	virtual void MarkFrame() = 0;

    void dumpMDL(const char* targetDir, safetyhook::InlineHook& hk_object, void* pFunction);
    static const char* getPathToMDL() { return target_dir.c_str(); }

private:
    inline static std::string target_dir;
};

inline void CMDLCache::dumpMDL(const char* targetDir, safetyhook::InlineHook& hk_object,  void* pFunction)
{
    target_dir = targetDir;
    if (!hk_object.enabled())
        hk_object = safetyhook::create_inline(MadFramework::Memory::GetVTableFunctionAddress(this, 0x23), pFunction);
}
