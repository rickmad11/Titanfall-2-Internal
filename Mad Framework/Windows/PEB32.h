#pragma once

struct _UNICODE_STRING { /* Size=0x8 */
/* 0x0000 */ public: uint16_t Length;
/* 0x0002 */ public: uint16_t MaximumLength;
/* 0x0004 */ public: wchar_t* Buffer;
};

struct _LEAP_SECOND_DATA { /* Size=0x10 */
/* 0x0000 */ public: unsigned char Enabled;
/* 0x0004 */ public: uint32_t Count;
/* 0x0008 */ public: _LARGE_INTEGER Data[1];
};

struct _STRING { /* Size=0x8 */
/* 0x0000 */ public: uint16_t Length;
/* 0x0002 */ public: uint16_t MaximumLength;
/* 0x0004 */ public: char* Buffer;
};

typedef struct _PEB_LDR_DATA { /* Size=0x30 */
/* 0x0000 */ public: uint32_t Length;
/* 0x0004 */ public: unsigned char Initialized;
/* 0x0008 */ public: void* SsHandle;
/* 0x000c */ public: _LIST_ENTRY InLoadOrderModuleList;
/* 0x0014 */ public: _LIST_ENTRY InMemoryOrderModuleList;
/* 0x001c */ public: _LIST_ENTRY InInitializationOrderModuleList;
/* 0x0024 */ public: void* EntryInProgress;
/* 0x0028 */ public: unsigned char ShutdownInProgress;
/* 0x002c */ public: void* ShutdownThreadId;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

struct _RTL_DRIVE_LETTER_CURDIR { /* Size=0x10 */
/* 0x0000 */ public: uint16_t Flags;
/* 0x0002 */ public: uint16_t Length;
/* 0x0004 */ public: uint32_t TimeStamp;
/* 0x0008 */ public: _STRING DosPath;
};

struct _CURDIR { /* Size=0xc */
/* 0x0000 */ public: _UNICODE_STRING DosPath;
/* 0x0008 */ public: void* Handle;
};

struct _RTL_USER_PROCESS_PARAMETERS { /* Size=0x2c4 */
/* 0x0000 */ public: uint32_t MaximumLength;
/* 0x0004 */ public: uint32_t Length;
/* 0x0008 */ public: uint32_t Flags;
/* 0x000c */ public: uint32_t DebugFlags;
/* 0x0010 */ public: void* ConsoleHandle;
/* 0x0014 */ public: uint32_t ConsoleFlags;
/* 0x0018 */ public: void* StandardInput;
/* 0x001c */ public: void* StandardOutput;
/* 0x0020 */ public: void* StandardError;
/* 0x0024 */ public: _CURDIR CurrentDirectory;
/* 0x0030 */ public: _UNICODE_STRING DllPath;
/* 0x0038 */ public: _UNICODE_STRING ImagePathName;
/* 0x0040 */ public: _UNICODE_STRING CommandLine;
/* 0x0048 */ public: void* Environment;
/* 0x004c */ public: uint32_t StartingX;
/* 0x0050 */ public: uint32_t StartingY;
/* 0x0054 */ public: uint32_t CountX;
/* 0x0058 */ public: uint32_t CountY;
/* 0x005c */ public: uint32_t CountCharsX;
/* 0x0060 */ public: uint32_t CountCharsY;
/* 0x0064 */ public: uint32_t FillAttribute;
/* 0x0068 */ public: uint32_t WindowFlags;
/* 0x006c */ public: uint32_t ShowWindowFlags;
/* 0x0070 */ public: _UNICODE_STRING WindowTitle;
/* 0x0078 */ public: _UNICODE_STRING DesktopInfo;
/* 0x0080 */ public: _UNICODE_STRING ShellInfo;
/* 0x0088 */ public: _UNICODE_STRING RuntimeData;
/* 0x0090 */ public: _RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
/* 0x0290 */ public: uint32_t EnvironmentSize;
/* 0x0294 */ public: uint32_t EnvironmentVersion;
/* 0x0298 */ public: void* PackageDependencyData;
/* 0x029c */ public: uint32_t ProcessGroupId;
/* 0x02a0 */ public: uint32_t LoaderThreads;
/* 0x02a4 */ public: _UNICODE_STRING RedirectionDllName;
/* 0x02ac */ public: _UNICODE_STRING HeapPartitionName;
/* 0x02b4 */ public: uint64_t* DefaultThreadpoolCpuSetMasks;
/* 0x02b8 */ public: uint32_t DefaultThreadpoolCpuSetMaskCount;
/* 0x02bc */ public: uint32_t DefaultThreadpoolThreadMaximum;
/* 0x02c0 */ public: uint32_t HeapMemoryTypeMask;
};

struct _RTL_BITMAP { /* Size=0x8 */
/* 0x0000 */ public: uint32_t SizeOfBitMap;
/* 0x0004 */ public: uint32_t* Buffer;
};

struct _ACTIVATION_CONTEXT_DATA { /* Size=0x20 */
/* 0x0000 */ public: uint32_t Magic;
/* 0x0004 */ public: uint32_t HeaderSize;
/* 0x0008 */ public: uint32_t FormatVersion;
/* 0x000c */ public: uint32_t TotalSize;
/* 0x0010 */ public: uint32_t DefaultTocOffset;
/* 0x0014 */ public: uint32_t ExtendedTocOffset;
/* 0x0018 */ public: uint32_t AssemblyRosterOffset;
/* 0x001c */ public: uint32_t Flags;
};

typedef struct _PEB { /* Size=0x488 */
/* 0x0000 */ public: unsigned char InheritedAddressSpace;
/* 0x0001 */ public: unsigned char ReadImageFileExecOptions;
/* 0x0002 */ public: unsigned char BeingDebugged;
                   union {
                   /* 0x0003 */ public: unsigned char BitField;
                                      struct _{
                                      /* 0x0003 */ public: unsigned char ImageUsesLargePages : 1; /* BitPos=0 */
                                      /* 0x0003 */ public: unsigned char IsProtectedProcess : 1; /* BitPos=1 */
                                      /* 0x0003 */ public: unsigned char IsImageDynamicallyRelocated : 1; /* BitPos=2 */
                                      /* 0x0003 */ public: unsigned char SkipPatchingUser32Forwarders : 1; /* BitPos=3 */
                                      /* 0x0003 */ public: unsigned char IsPackagedProcess : 1; /* BitPos=4 */
                                      /* 0x0003 */ public: unsigned char IsAppContainer : 1; /* BitPos=5 */
                                      /* 0x0003 */ public: unsigned char IsProtectedProcessLight : 1; /* BitPos=6 */
                                      /* 0x0003 */ public: unsigned char IsLongPathAwareProcess : 1; /* BitPos=7 */
                                      };
                   };
/* 0x0004 */ public: void* Mutant;
/* 0x0008 */ public: void* ImageBaseAddress;
/* 0x000c */ public: _PEB_LDR_DATA* Ldr;
/* 0x0010 */ public: _RTL_USER_PROCESS_PARAMETERS* ProcessParameters;
/* 0x0014 */ public: void* SubSystemData;
/* 0x0018 */ public: void* ProcessHeap;
/* 0x001c */ public: _RTL_CRITICAL_SECTION* FastPebLock;
/* 0x0020 */ public: _SLIST_HEADER* AtlThunkSListPtr;
/* 0x0024 */ public: void* IFEOKey;
                   union {
                   /* 0x0028 */ public: uint32_t CrossProcessFlags;
                                      struct _{
                                      /* 0x0028 */ public: uint32_t ProcessInJob : 1; /* BitPos=0 */
                                      /* 0x0028 */ public: uint32_t ProcessInitializing : 1; /* BitPos=1 */
                                      /* 0x0028 */ public: uint32_t ProcessUsingVEH : 1; /* BitPos=2 */
                                      /* 0x0028 */ public: uint32_t ProcessUsingVCH : 1; /* BitPos=3 */
                                      /* 0x0028 */ public: uint32_t ProcessUsingFTH : 1; /* BitPos=4 */
                                      /* 0x0028 */ public: uint32_t ProcessPreviouslyThrottled : 1; /* BitPos=5 */
                                      /* 0x0028 */ public: uint32_t ProcessCurrentlyThrottled : 1; /* BitPos=6 */
                                      /* 0x0028 */ public: uint32_t ProcessImagesHotPatched : 1; /* BitPos=7 */
                                      /* 0x0028 */ public: uint32_t ReservedBits0 : 24; /* BitPos=8 */
                                      };
                   };
                   union {
                   /* 0x002c */ public: void* KernelCallbackTable;
                   /* 0x002c */ public: void* UserSharedInfoPtr;
                   };
/* 0x0030 */ public: uint32_t SystemReserved;
/* 0x0034 */ public: _SLIST_HEADER* AtlThunkSListPtr32;
/* 0x0038 */ public: void* ApiSetMap;
/* 0x003c */ public: uint32_t TlsExpansionCounter;
/* 0x0040 */ public: _RTL_BITMAP* TlsBitmap;
/* 0x0044 */ public: uint32_t TlsBitmapBits[2];
/* 0x004c */ public: void* ReadOnlySharedMemoryBase;
/* 0x0050 */ public: void* SharedData;
/* 0x0054 */ public: void** ReadOnlyStaticServerData;
/* 0x0058 */ public: void* AnsiCodePageData;
/* 0x005c */ public: void* OemCodePageData;
/* 0x0060 */ public: void* UnicodeCaseTableData;
/* 0x0064 */ public: uint32_t NumberOfProcessors;
/* 0x0068 */ public: uint32_t NtGlobalFlag;
/* 0x0070 */ public: _LARGE_INTEGER CriticalSectionTimeout;
/* 0x0078 */ public: uint32_t HeapSegmentReserve;
/* 0x007c */ public: uint32_t HeapSegmentCommit;
/* 0x0080 */ public: uint32_t HeapDeCommitTotalFreeThreshold;
/* 0x0084 */ public: uint32_t HeapDeCommitFreeBlockThreshold;
/* 0x0088 */ public: uint32_t NumberOfHeaps;
/* 0x008c */ public: uint32_t MaximumNumberOfHeaps;
/* 0x0090 */ public: void** ProcessHeaps;
/* 0x0094 */ public: void* GdiSharedHandleTable;
/* 0x0098 */ public: void* ProcessStarterHelper;
/* 0x009c */ public: uint32_t GdiDCAttributeList;
/* 0x00a0 */ public: _RTL_CRITICAL_SECTION* LoaderLock;
/* 0x00a4 */ public: uint32_t OSMajorVersion;
/* 0x00a8 */ public: uint32_t OSMinorVersion;
/* 0x00ac */ public: uint16_t OSBuildNumber;
/* 0x00ae */ public: uint16_t OSCSDVersion;
/* 0x00b0 */ public: uint32_t OSPlatformId;
/* 0x00b4 */ public: uint32_t ImageSubsystem;
/* 0x00b8 */ public: uint32_t ImageSubsystemMajorVersion;
/* 0x00bc */ public: uint32_t ImageSubsystemMinorVersion;
/* 0x00c0 */ public: uint32_t ActiveProcessAffinityMask;
/* 0x00c4 */ public: uint32_t GdiHandleBuffer[34];
/* 0x014c */ public: void (*PostProcessInitRoutine)();
/* 0x0150 */ public: _RTL_BITMAP* TlsExpansionBitmap;
/* 0x0154 */ public: uint32_t TlsExpansionBitmapBits[32];
/* 0x01d4 */ public: uint32_t SessionId;
/* 0x01d8 */ public: _ULARGE_INTEGER AppCompatFlags;
/* 0x01e0 */ public: _ULARGE_INTEGER AppCompatFlagsUser;
/* 0x01e8 */ public: void* pShimData;
/* 0x01ec */ public: void* AppCompatInfo;
/* 0x01f0 */ public: _UNICODE_STRING CSDVersion;
/* 0x01f8 */ public: const _ACTIVATION_CONTEXT_DATA* ActivationContextData;
/* 0x01fc */ public: void* ProcessAssemblyStorageMap;
/* 0x0200 */ public: const _ACTIVATION_CONTEXT_DATA* SystemDefaultActivationContextData;
/* 0x0204 */ public: void* SystemAssemblyStorageMap;
/* 0x0208 */ public: uint32_t MinimumStackCommit;
/* 0x020c */ public: void* SparePointers[2];
/* 0x0214 */ public: void* PatchLoaderData;
/* 0x0218 */ public: void* ChpeV2ProcessInfo;
/* 0x021c */ public: uint32_t AppModelFeatureState;
/* 0x0220 */ public: uint32_t SpareUlongs[2];
/* 0x0228 */ public: uint16_t ActiveCodePage;
/* 0x022a */ public: uint16_t OemCodePage;
/* 0x022c */ public: uint16_t UseCaseMapping;
/* 0x022e */ public: uint16_t UnusedNlsField;
/* 0x0230 */ public: void* WerRegistrationData;
/* 0x0234 */ public: void* WerShipAssertPtr;
/* 0x0238 */ public: void* Spare;
/* 0x023c */ public: void* pImageHeaderHash;
                   union {
                   /* 0x0240 */ public: uint32_t TracingFlags;
                                      struct _{
                                      /* 0x0240 */ public: uint32_t HeapTracingEnabled : 1; /* BitPos=0 */
                                      /* 0x0240 */ public: uint32_t CritSecTracingEnabled : 1; /* BitPos=1 */
                                      /* 0x0240 */ public: uint32_t LibLoaderTracingEnabled : 1; /* BitPos=2 */
                                      /* 0x0240 */ public: uint32_t SpareTracingBits : 29; /* BitPos=3 */
                                      };
                   };
/* 0x0248 */ public: uint64_t CsrServerReadOnlySharedMemoryBase;
/* 0x0250 */ public: uint32_t TppWorkerpListLock;
/* 0x0254 */ public: _LIST_ENTRY TppWorkerpList;
/* 0x025c */ public: void* WaitOnAddressHashTable[128];
/* 0x045c */ public: void* TelemetryCoverageHeader;
/* 0x0460 */ public: uint32_t CloudFileFlags;
/* 0x0464 */ public: uint32_t CloudFileDiagFlags;
/* 0x0468 */ public: char PlaceholderCompatibilityMode;
/* 0x0469 */ public: char PlaceholderCompatibilityModeReserved[7];
/* 0x0470 */ public: _LEAP_SECOND_DATA* LeapSecondData;
                   union {
                   /* 0x0474 */ public: uint32_t LeapSecondFlags;
                                      struct _{
                                      /* 0x0474 */ public: uint32_t SixtySecondEnabled : 1; /* BitPos=0 */
                                      /* 0x0474 */ public: uint32_t Reserved : 31; /* BitPos=1 */
                                      };
                   };
/* 0x0478 */ public: uint32_t NtGlobalFlag2;
/* 0x0480 */ public: uint64_t ExtendedFeatureDisableMask;
} PEB, * PPEB;

struct _RTL_BALANCED_NODE { /* Size=0xc */
    union {
    /* 0x0000 */ public: _RTL_BALANCED_NODE* Children[2];
                       struct _{
                       /* 0x0000 */ public: _RTL_BALANCED_NODE* Left;
                       /* 0x0004 */ public: _RTL_BALANCED_NODE* Right;
                       };
    };
    union {
    /* 0x0008 */ public: unsigned char Red : 1; /* BitPos=0 */
    /* 0x0008 */ public: unsigned char Balance : 2; /* BitPos=0 */
    /* 0x0008 */ public: uint32_t ParentValue;
    };
};

enum _LDR_DLL_LOAD_REASON : int32_t {
    LoadReasonStaticDependency = 0x0000,
    LoadReasonStaticForwarderDependency = 0x0001,
    LoadReasonDynamicForwarderDependency = 0x0002,
    LoadReasonDelayloadDependency = 0x0003,
    LoadReasonDynamicLoad = 0x0004,
    LoadReasonAsImageLoad = 0x0005,
    LoadReasonAsDataLoad = 0x0006,
    LoadReasonEnclavePrimary = 0x0007,
    LoadReasonEnclaveDependency = 0x0008,
    LoadReasonPatchImage = 0x0009,
    LoadReasonUnknown = 0xff,
};

enum _LDR_HOT_PATCH_STATE : int32_t {
    LdrHotPatchBaseImage = 0x0000,
    LdrHotPatchNotApplied = 0x0001,
    LdrHotPatchAppliedReverse = 0x0002,
    LdrHotPatchAppliedForward = 0x0003,
    LdrHotPatchFailedToPatch = 0x0004,
    LdrHotPatchStateMax = 0x0005,
};

typedef struct _LDR_DATA_TABLE_ENTRY { /* Size=0xb8 */
/* 0x0000 */ public: _LIST_ENTRY InLoadOrderLinks;
/* 0x0008 */ public: _LIST_ENTRY InMemoryOrderLinks;
/* 0x0010 */ public: _LIST_ENTRY InInitializationOrderLinks;
/* 0x0018 */ public: void* DllBase;
/* 0x001c */ public: void* EntryPoint;
/* 0x0020 */ public: uint32_t SizeOfImage;
/* 0x0024 */ public: _UNICODE_STRING FullDllName;
/* 0x002c */ public: _UNICODE_STRING BaseDllName;
                   union {
                   /* 0x0034 */ public: unsigned char FlagGroup[4];
                   /* 0x0034 */ public: uint32_t Flags;
                                      struct _{
                                      /* 0x0034 */ public: uint32_t PackagedBinary : 1; /* BitPos=0 */
                                      /* 0x0034 */ public: uint32_t MarkedForRemoval : 1; /* BitPos=1 */
                                      /* 0x0034 */ public: uint32_t ImageDll : 1; /* BitPos=2 */
                                      /* 0x0034 */ public: uint32_t LoadNotificationsSent : 1; /* BitPos=3 */
                                      /* 0x0034 */ public: uint32_t TelemetryEntryProcessed : 1; /* BitPos=4 */
                                      /* 0x0034 */ public: uint32_t ProcessStaticImport : 1; /* BitPos=5 */
                                      /* 0x0034 */ public: uint32_t InLegacyLists : 1; /* BitPos=6 */
                                      /* 0x0034 */ public: uint32_t InIndexes : 1; /* BitPos=7 */
                                      /* 0x0034 */ public: uint32_t ShimDll : 1; /* BitPos=8 */
                                      /* 0x0034 */ public: uint32_t InExceptionTable : 1; /* BitPos=9 */
                                      /* 0x0034 */ public: uint32_t VerifierProvider : 1; /* BitPos=10 */
                                      /* 0x0034 */ public: uint32_t ShimEngineCalloutSent : 1; /* BitPos=11 */
                                      /* 0x0034 */ public: uint32_t LoadInProgress : 1; /* BitPos=12 */
                                      /* 0x0034 */ public: uint32_t LoadConfigProcessed : 1; /* BitPos=13 */
                                      /* 0x0034 */ public: uint32_t EntryProcessed : 1; /* BitPos=14 */
                                      /* 0x0034 */ public: uint32_t ProtectDelayLoad : 1; /* BitPos=15 */
                                      /* 0x0034 */ public: uint32_t AuxIatCopyPrivate : 1; /* BitPos=16 */
                                      /* 0x0034 */ public: uint32_t ReservedFlags3 : 1; /* BitPos=17 */
                                      /* 0x0034 */ public: uint32_t DontCallForThreads : 1; /* BitPos=18 */
                                      /* 0x0034 */ public: uint32_t ProcessAttachCalled : 1; /* BitPos=19 */
                                      /* 0x0034 */ public: uint32_t ProcessAttachFailed : 1; /* BitPos=20 */
                                      /* 0x0034 */ public: uint32_t ScpInExceptionTable : 1; /* BitPos=21 */
                                      /* 0x0034 */ public: uint32_t CorImage : 1; /* BitPos=22 */
                                      /* 0x0034 */ public: uint32_t DontRelocate : 1; /* BitPos=23 */
                                      /* 0x0034 */ public: uint32_t CorILOnly : 1; /* BitPos=24 */
                                      /* 0x0034 */ public: uint32_t ChpeImage : 1; /* BitPos=25 */
                                      /* 0x0034 */ public: uint32_t ChpeEmulatorImage : 1; /* BitPos=26 */
                                      /* 0x0034 */ public: uint32_t ReservedFlags5 : 1; /* BitPos=27 */
                                      /* 0x0034 */ public: uint32_t Redirected : 1; /* BitPos=28 */
                                      /* 0x0034 */ public: uint32_t ReservedFlags6 : 2; /* BitPos=29 */
                                      /* 0x0034 */ public: uint32_t CompatDatabaseProcessed : 1; /* BitPos=31 */
                                      };
                   };
/* 0x0038 */ public: uint16_t ObsoleteLoadCount;
/* 0x003a */ public: uint16_t TlsIndex;
/* 0x003c */ public: _LIST_ENTRY HashLinks;
/* 0x0044 */ public: uint32_t TimeDateStamp;
/* 0x0048 */ public: _ACTIVATION_CONTEXT* EntryPointActivationContext;
/* 0x004c */ public: void* Lock;
/* 0x0050 */ public: void* DdagNode;
/* 0x0054 */ public: _LIST_ENTRY NodeModuleLink;
/* 0x005c */ public: void* LoadContext;
/* 0x0060 */ public: void* ParentDllBase;
/* 0x0064 */ public: void* SwitchBackContext;
/* 0x0068 */ public: _RTL_BALANCED_NODE BaseAddressIndexNode;
/* 0x0074 */ public: _RTL_BALANCED_NODE MappingInfoIndexNode;
/* 0x0080 */ public: uint32_t OriginalBase;
/* 0x0088 */ public: _LARGE_INTEGER LoadTime;
/* 0x0090 */ public: uint32_t BaseNameHashValue;
/* 0x0094 */ public: _LDR_DLL_LOAD_REASON LoadReason;
/* 0x0098 */ public: uint32_t ImplicitPathOptions;
/* 0x009c */ public: uint32_t ReferenceCount;
/* 0x00a0 */ public: uint32_t DependentLoadFlags;
/* 0x00a4 */ public: unsigned char SigningLevel;
/* 0x00a8 */ public: uint32_t CheckSum;
/* 0x00ac */ public: void* ActivePatchImageBase;
/* 0x00b0 */ public: _LDR_HOT_PATCH_STATE HotPatchState;
}LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;