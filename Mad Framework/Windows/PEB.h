#pragma once

#ifndef _WIN64
#include "PEB32.h"
#else

struct _LEAP_SECOND_DATA { /* Size=0x10 */
/* 0x0000 */ public: unsigned char Enabled;
/* 0x0004 */ public: uint32_t Count;
/* 0x0008 */ public: _LARGE_INTEGER Data[1];
};

typedef struct _ACTIVATION_CONTEXT_DATA { /* Size=0x20 */
/* 0x0000 */ public: uint32_t Magic;
/* 0x0004 */ public: uint32_t HeaderSize;
/* 0x0008 */ public: uint32_t FormatVersion;
/* 0x000c */ public: uint32_t TotalSize;
/* 0x0010 */ public: uint32_t DefaultTocOffset;
/* 0x0014 */ public: uint32_t ExtendedTocOffset;
/* 0x0018 */ public: uint32_t AssemblyRosterOffset;
/* 0x001c */ public: uint32_t Flags;
}ACTIVATION_CONTEXT_DATA, *PACTIVATION_CONTEXT_DATA;

typedef struct _UNICODE_STRING { /* Size=0x10 */
/* 0x0000 */ public: uint16_t Length;
/* 0x0002 */ public: uint16_t MaximumLength;
/* 0x0008 */ public: wchar_t* Buffer;
}UNICODE_STRING, * PUNICODE_STRING;

typedef struct _STRING { /* Size=0x10 */
/* 0x0000 */ public: uint16_t Length;
/* 0x0002 */ public: uint16_t MaximumLength;
/* 0x0008 */ public: char* Buffer;
}STRING, *PSTRING;

typedef struct _RTL_DRIVE_LETTER_CURDIR { /* Size=0x18 */
/* 0x0000 */ public: uint16_t Flags;
/* 0x0002 */ public: uint16_t Length;
/* 0x0004 */ public: uint32_t TimeStamp;
/* 0x0008 */ public: _STRING DosPath;
}RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _CURDIR { /* Size=0x18 */
/* 0x0000 */ public: _UNICODE_STRING DosPath;
/* 0x0010 */ public: void* Handle;
}CURDIR, *PCURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS { /* Size=0x448 */
/* 0x0000 */ public: uint32_t MaximumLength;
/* 0x0004 */ public: uint32_t Length;
/* 0x0008 */ public: uint32_t Flags;
/* 0x000c */ public: uint32_t DebugFlags;
/* 0x0010 */ public: void* ConsoleHandle;
/* 0x0018 */ public: uint32_t ConsoleFlags;
/* 0x0020 */ public: void* StandardInput;
/* 0x0028 */ public: void* StandardOutput;
/* 0x0030 */ public: void* StandardError;
/* 0x0038 */ public: _CURDIR CurrentDirectory;
/* 0x0050 */ public: _UNICODE_STRING DllPath;
/* 0x0060 */ public: _UNICODE_STRING ImagePathName;
/* 0x0070 */ public: _UNICODE_STRING CommandLine;
/* 0x0080 */ public: void* Environment;
/* 0x0088 */ public: uint32_t StartingX;
/* 0x008c */ public: uint32_t StartingY;
/* 0x0090 */ public: uint32_t CountX;
/* 0x0094 */ public: uint32_t CountY;
/* 0x0098 */ public: uint32_t CountCharsX;
/* 0x009c */ public: uint32_t CountCharsY;
/* 0x00a0 */ public: uint32_t FillAttribute;
/* 0x00a4 */ public: uint32_t WindowFlags;
/* 0x00a8 */ public: uint32_t ShowWindowFlags;
/* 0x00b0 */ public: _UNICODE_STRING WindowTitle;
/* 0x00c0 */ public: _UNICODE_STRING DesktopInfo;
/* 0x00d0 */ public: _UNICODE_STRING ShellInfo;
/* 0x00e0 */ public: _UNICODE_STRING RuntimeData;
/* 0x00f0 */ public: _RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
/* 0x03f0 */ public: uint64_t EnvironmentSize;
/* 0x03f8 */ public: uint64_t EnvironmentVersion;
/* 0x0400 */ public: void* PackageDependencyData;
/* 0x0408 */ public: uint32_t ProcessGroupId;
/* 0x040c */ public: uint32_t LoaderThreads;
/* 0x0410 */ public: _UNICODE_STRING RedirectionDllName;
/* 0x0420 */ public: _UNICODE_STRING HeapPartitionName;
/* 0x0430 */ public: uint64_t* DefaultThreadpoolCpuSetMasks;
/* 0x0438 */ public: uint32_t DefaultThreadpoolCpuSetMaskCount;
/* 0x043c */ public: uint32_t DefaultThreadpoolThreadMaximum;
/* 0x0440 */ public: uint32_t HeapMemoryTypeMask;
}RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _PEB_LDR_DATA { /* Size=0x58 */
/* 0x0000 */ public: uint32_t Length;
/* 0x0004 */ public: unsigned char Initialized;
/* 0x0008 */ public: void* SsHandle;
/* 0x0010 */ public: _LIST_ENTRY InLoadOrderModuleList;
/* 0x0020 */ public: _LIST_ENTRY InMemoryOrderModuleList;
/* 0x0030 */ public: _LIST_ENTRY InInitializationOrderModuleList;
/* 0x0040 */ public: void* EntryInProgress;
/* 0x0048 */ public: unsigned char ShutdownInProgress;
/* 0x0050 */ public: void* ShutdownThreadId;
}PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _RTL_BITMAP { /* Size=0x10 */
/* 0x0000 */ public: uint32_t SizeOfBitMap;
/* 0x0008 */ public: uint32_t* Buffer;
}RTL_BITMAP, *PRTL_BITMAP;

typedef struct _PEB { /* Size=0x7d0 */
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
/* 0x0004 */ public: unsigned char Padding0[4];
/* 0x0008 */ public: void* Mutant;
/* 0x0010 */ public: void* ImageBaseAddress;
/* 0x0018 */ public: _PEB_LDR_DATA* Ldr;
/* 0x0020 */ public: _RTL_USER_PROCESS_PARAMETERS* ProcessParameters;
/* 0x0028 */ public: void* SubSystemData;
/* 0x0030 */ public: void* ProcessHeap;
/* 0x0038 */ public: _RTL_CRITICAL_SECTION* FastPebLock;
/* 0x0040 */ public: _SLIST_HEADER* AtlThunkSListPtr;
/* 0x0048 */ public: void* IFEOKey;
                   union {
                   /* 0x0050 */ public: uint32_t CrossProcessFlags;
                                      struct _{
                                      /* 0x0050 */ public: uint32_t ProcessInJob : 1; /* BitPos=0 */
                                      /* 0x0050 */ public: uint32_t ProcessInitializing : 1; /* BitPos=1 */
                                      /* 0x0050 */ public: uint32_t ProcessUsingVEH : 1; /* BitPos=2 */
                                      /* 0x0050 */ public: uint32_t ProcessUsingVCH : 1; /* BitPos=3 */
                                      /* 0x0050 */ public: uint32_t ProcessUsingFTH : 1; /* BitPos=4 */
                                      /* 0x0050 */ public: uint32_t ProcessPreviouslyThrottled : 1; /* BitPos=5 */
                                      /* 0x0050 */ public: uint32_t ProcessCurrentlyThrottled : 1; /* BitPos=6 */
                                      /* 0x0050 */ public: uint32_t ProcessImagesHotPatched : 1; /* BitPos=7 */
                                      /* 0x0050 */ public: uint32_t ReservedBits0 : 24; /* BitPos=8 */
                                      };
                   };
/* 0x0054 */ public: unsigned char Padding1[4];
                   union {
                   /* 0x0058 */ public: void* KernelCallbackTable;
                   /* 0x0058 */ public: void* UserSharedInfoPtr;
                   };
/* 0x0060 */ public: uint32_t SystemReserved;
/* 0x0064 */ public: uint32_t AtlThunkSListPtr32;
/* 0x0068 */ public: void* ApiSetMap;
/* 0x0070 */ public: uint32_t TlsExpansionCounter;
/* 0x0074 */ public: unsigned char Padding2[4];
/* 0x0078 */ public: _RTL_BITMAP* TlsBitmap;
/* 0x0080 */ public: uint32_t TlsBitmapBits[2];
/* 0x0088 */ public: void* ReadOnlySharedMemoryBase;
/* 0x0090 */ public: void* SharedData;
/* 0x0098 */ public: void** ReadOnlyStaticServerData;
/* 0x00a0 */ public: void* AnsiCodePageData;
/* 0x00a8 */ public: void* OemCodePageData;
/* 0x00b0 */ public: void* UnicodeCaseTableData;
/* 0x00b8 */ public: uint32_t NumberOfProcessors;
/* 0x00bc */ public: uint32_t NtGlobalFlag;
/* 0x00c0 */ public: _LARGE_INTEGER CriticalSectionTimeout;
/* 0x00c8 */ public: uint64_t HeapSegmentReserve;
/* 0x00d0 */ public: uint64_t HeapSegmentCommit;
/* 0x00d8 */ public: uint64_t HeapDeCommitTotalFreeThreshold;
/* 0x00e0 */ public: uint64_t HeapDeCommitFreeBlockThreshold;
/* 0x00e8 */ public: uint32_t NumberOfHeaps;
/* 0x00ec */ public: uint32_t MaximumNumberOfHeaps;
/* 0x00f0 */ public: void** ProcessHeaps;
/* 0x00f8 */ public: void* GdiSharedHandleTable;
/* 0x0100 */ public: void* ProcessStarterHelper;
/* 0x0108 */ public: uint32_t GdiDCAttributeList;
/* 0x010c */ public: unsigned char Padding3[4];
/* 0x0110 */ public: _RTL_CRITICAL_SECTION* LoaderLock;
/* 0x0118 */ public: uint32_t OSMajorVersion;
/* 0x011c */ public: uint32_t OSMinorVersion;
/* 0x0120 */ public: uint16_t OSBuildNumber;
/* 0x0122 */ public: uint16_t OSCSDVersion;
/* 0x0124 */ public: uint32_t OSPlatformId;
/* 0x0128 */ public: uint32_t ImageSubsystem;
/* 0x012c */ public: uint32_t ImageSubsystemMajorVersion;
/* 0x0130 */ public: uint32_t ImageSubsystemMinorVersion;
/* 0x0134 */ public: unsigned char Padding4[4];
/* 0x0138 */ public: uint64_t ActiveProcessAffinityMask;
/* 0x0140 */ public: uint32_t GdiHandleBuffer[60];
/* 0x0230 */ public: void (*PostProcessInitRoutine)();
/* 0x0238 */ public: _RTL_BITMAP* TlsExpansionBitmap;
/* 0x0240 */ public: uint32_t TlsExpansionBitmapBits[32];
/* 0x02c0 */ public: uint32_t SessionId;
/* 0x02c4 */ public: unsigned char Padding5[4];
/* 0x02c8 */ public: _ULARGE_INTEGER AppCompatFlags;
/* 0x02d0 */ public: _ULARGE_INTEGER AppCompatFlagsUser;
/* 0x02d8 */ public: void* pShimData;
/* 0x02e0 */ public: void* AppCompatInfo;
/* 0x02e8 */ public: _UNICODE_STRING CSDVersion;
/* 0x02f8 */ public: const _ACTIVATION_CONTEXT_DATA* ActivationContextData;
/* 0x0300 */ public: void* ProcessAssemblyStorageMap;
/* 0x0308 */ public: const _ACTIVATION_CONTEXT_DATA* SystemDefaultActivationContextData;
/* 0x0310 */ public: void* SystemAssemblyStorageMap;
/* 0x0318 */ public: uint64_t MinimumStackCommit;
/* 0x0320 */ public: void* SparePointers[2];
/* 0x0330 */ public: void* PatchLoaderData;
/* 0x0338 */ public: void* ChpeV2ProcessInfo;
/* 0x0340 */ public: uint32_t AppModelFeatureState;
/* 0x0344 */ public: uint32_t SpareUlongs[2];
/* 0x034c */ public: uint16_t ActiveCodePage;
/* 0x034e */ public: uint16_t OemCodePage;
/* 0x0350 */ public: uint16_t UseCaseMapping;
/* 0x0352 */ public: uint16_t UnusedNlsField;
/* 0x0358 */ public: void* WerRegistrationData;
/* 0x0360 */ public: void* WerShipAssertPtr;
/* 0x0368 */ public: void* EcCodeBitMap;
/* 0x0370 */ public: void* pImageHeaderHash;
                   union {
                   /* 0x0378 */ public: uint32_t TracingFlags;
                                      struct _{
                                      /* 0x0378 */ public: uint32_t HeapTracingEnabled : 1; /* BitPos=0 */
                                      /* 0x0378 */ public: uint32_t CritSecTracingEnabled : 1; /* BitPos=1 */
                                      /* 0x0378 */ public: uint32_t LibLoaderTracingEnabled : 1; /* BitPos=2 */
                                      /* 0x0378 */ public: uint32_t SpareTracingBits : 29; /* BitPos=3 */
                                      };
                   };
/* 0x037c */ public: unsigned char Padding6[4];
/* 0x0380 */ public: uint64_t CsrServerReadOnlySharedMemoryBase;
/* 0x0388 */ public: uint64_t TppWorkerpListLock;
/* 0x0390 */ public: _LIST_ENTRY TppWorkerpList;
/* 0x03a0 */ public: void* WaitOnAddressHashTable[128];
/* 0x07a0 */ public: void* TelemetryCoverageHeader;
/* 0x07a8 */ public: uint32_t CloudFileFlags;
/* 0x07ac */ public: uint32_t CloudFileDiagFlags;
/* 0x07b0 */ public: char PlaceholderCompatibilityMode;
/* 0x07b1 */ public: char PlaceholderCompatibilityModeReserved[7];
/* 0x07b8 */ public: _LEAP_SECOND_DATA* LeapSecondData;
                   union {
                   /* 0x07c0 */ public: uint32_t LeapSecondFlags;
                                      struct _{
                                      /* 0x07c0 */ public: uint32_t SixtySecondEnabled : 1; /* BitPos=0 */
                                      /* 0x07c0 */ public: uint32_t Reserved : 31; /* BitPos=1 */
                                      };
                   };
/* 0x07c4 */ public: uint32_t NtGlobalFlag2;
/* 0x07c8 */ public: uint64_t ExtendedFeatureDisableMask;
} PEB, * PPEB;

enum _LDR_DDAG_STATE : int32_t {
    LdrModulesMerged = 0xfb,
    LdrModulesInitError = 0xfc,
    LdrModulesSnapError = 0xfd,
    LdrModulesUnloaded = 0xfe,
    LdrModulesUnloading = 0xff,
    LdrModulesPlaceHolder = 0x0000,
    LdrModulesMapping = 0x0001,
    LdrModulesMapped = 0x0002,
    LdrModulesWaitingForDependencies = 0x0003,
    LdrModulesSnapping = 0x0004,
    LdrModulesSnapped = 0x0005,
    LdrModulesCondensed = 0x0006,
    LdrModulesReadyToInit = 0x0007,
    LdrModulesInitializing = 0x0008,
    LdrModulesReadyToRun = 0x0009,
};

typedef struct _LDR_DDAG_NODE { /* Size=0x50 */
/* 0x0000 */ public: _LIST_ENTRY Modules;
/* 0x0010 */ public: void* ServiceTagList;
/* 0x0018 */ public: uint32_t LoadCount;
/* 0x001c */ public: uint32_t LoadWhileUnloadingCount;
/* 0x0020 */ public: uint32_t LowestLink;
/* 0x0028 */ public: void* Dependencies;
/* 0x0030 */ public: void* IncomingDependencies;
/* 0x0038 */ public: _LDR_DDAG_STATE State;
/* 0x0040 */ public: _SINGLE_LIST_ENTRY CondenseLink;
/* 0x0048 */ public: uint32_t PreorderNumber;
}LDR_DDAG_NODE, *PLDR_DDAG_NODE;

enum _LDR_HOT_PATCH_STATE : int32_t {
    LdrHotPatchBaseImage = 0x0000,
    LdrHotPatchNotApplied = 0x0001,
    LdrHotPatchAppliedReverse = 0x0002,
    LdrHotPatchAppliedForward = 0x0003,
    LdrHotPatchFailedToPatch = 0x0004,
    LdrHotPatchStateMax = 0x0005,
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

typedef struct _RTL_BALANCED_NODE { /* Size=0x18 */
    union {
    /* 0x0000 */ public: _RTL_BALANCED_NODE* Children[2];
                       struct _{
                       /* 0x0000 */ public: _RTL_BALANCED_NODE* Left;
                       /* 0x0008 */ public: _RTL_BALANCED_NODE* Right;
                       };
    };
    union {
    /* 0x0010 */ public: unsigned char Red : 1; /* BitPos=0 */
    /* 0x0010 */ public: unsigned char Balance : 2; /* BitPos=0 */
    /* 0x0010 */ public: uint64_t ParentValue;
    };
}RTL_BALANCED_NODE, * PRTL_BALANCED_NODE;

typedef struct _LDR_DATA_TABLE_ENTRY { /* Size=0x138 */
/* 0x0000 */ public: _LIST_ENTRY InLoadOrderLinks;
/* 0x0010 */ public: _LIST_ENTRY InMemoryOrderLinks;
/* 0x0020 */ public: _LIST_ENTRY InInitializationOrderLinks;
/* 0x0030 */ public: void* DllBase;
/* 0x0038 */ public: void* EntryPoint;
/* 0x0040 */ public: uint32_t SizeOfImage;
/* 0x0048 */ public: _UNICODE_STRING FullDllName;
/* 0x0058 */ public: _UNICODE_STRING BaseDllName;
                   union {
                   /* 0x0068 */ public: unsigned char FlagGroup[4];
                   /* 0x0068 */ public: uint32_t Flags;
                                      struct _{
                                      /* 0x0068 */ public: uint32_t PackagedBinary : 1; /* BitPos=0 */
                                      /* 0x0068 */ public: uint32_t MarkedForRemoval : 1; /* BitPos=1 */
                                      /* 0x0068 */ public: uint32_t ImageDll : 1; /* BitPos=2 */
                                      /* 0x0068 */ public: uint32_t LoadNotificationsSent : 1; /* BitPos=3 */
                                      /* 0x0068 */ public: uint32_t TelemetryEntryProcessed : 1; /* BitPos=4 */
                                      /* 0x0068 */ public: uint32_t ProcessStaticImport : 1; /* BitPos=5 */
                                      /* 0x0068 */ public: uint32_t InLegacyLists : 1; /* BitPos=6 */
                                      /* 0x0068 */ public: uint32_t InIndexes : 1; /* BitPos=7 */
                                      /* 0x0068 */ public: uint32_t ShimDll : 1; /* BitPos=8 */
                                      /* 0x0068 */ public: uint32_t InExceptionTable : 1; /* BitPos=9 */
                                      /* 0x0068 */ public: uint32_t VerifierProvider : 1; /* BitPos=10 */
                                      /* 0x0068 */ public: uint32_t ShimEngineCalloutSent : 1; /* BitPos=11 */
                                      /* 0x0068 */ public: uint32_t LoadInProgress : 1; /* BitPos=12 */
                                      /* 0x0068 */ public: uint32_t LoadConfigProcessed : 1; /* BitPos=13 */
                                      /* 0x0068 */ public: uint32_t EntryProcessed : 1; /* BitPos=14 */
                                      /* 0x0068 */ public: uint32_t ProtectDelayLoad : 1; /* BitPos=15 */
                                      /* 0x0068 */ public: uint32_t AuxIatCopyPrivate : 1; /* BitPos=16 */
                                      /* 0x0068 */ public: uint32_t ReservedFlags3 : 1; /* BitPos=17 */
                                      /* 0x0068 */ public: uint32_t DontCallForThreads : 1; /* BitPos=18 */
                                      /* 0x0068 */ public: uint32_t ProcessAttachCalled : 1; /* BitPos=19 */
                                      /* 0x0068 */ public: uint32_t ProcessAttachFailed : 1; /* BitPos=20 */
                                      /* 0x0068 */ public: uint32_t ScpInExceptionTable : 1; /* BitPos=21 */
                                      /* 0x0068 */ public: uint32_t CorImage : 1; /* BitPos=22 */
                                      /* 0x0068 */ public: uint32_t DontRelocate : 1; /* BitPos=23 */
                                      /* 0x0068 */ public: uint32_t CorILOnly : 1; /* BitPos=24 */
                                      /* 0x0068 */ public: uint32_t ChpeImage : 1; /* BitPos=25 */
                                      /* 0x0068 */ public: uint32_t ChpeEmulatorImage : 1; /* BitPos=26 */
                                      /* 0x0068 */ public: uint32_t ReservedFlags5 : 1; /* BitPos=27 */
                                      /* 0x0068 */ public: uint32_t Redirected : 1; /* BitPos=28 */
                                      /* 0x0068 */ public: uint32_t ReservedFlags6 : 2; /* BitPos=29 */
                                      /* 0x0068 */ public: uint32_t CompatDatabaseProcessed : 1; /* BitPos=31 */
                                      };
                   };
/* 0x006c */ public: uint16_t ObsoleteLoadCount;
/* 0x006e */ public: uint16_t TlsIndex;
/* 0x0070 */ public: _LIST_ENTRY HashLinks;
/* 0x0080 */ public: uint32_t TimeDateStamp;
/* 0x0088 */ public: _ACTIVATION_CONTEXT* EntryPointActivationContext;
/* 0x0090 */ public: void* Lock;
/* 0x0098 */ public: _LDR_DDAG_NODE* DdagNode;
/* 0x00a0 */ public: _LIST_ENTRY NodeModuleLink;
/* 0x00b0 */ public: void* LoadContext;
/* 0x00b8 */ public: void* ParentDllBase;
/* 0x00c0 */ public: void* SwitchBackContext;
/* 0x00c8 */ public: _RTL_BALANCED_NODE BaseAddressIndexNode;
/* 0x00e0 */ public: _RTL_BALANCED_NODE MappingInfoIndexNode;
/* 0x00f8 */ public: uint64_t OriginalBase;
/* 0x0100 */ public: _LARGE_INTEGER LoadTime;
/* 0x0108 */ public: uint32_t BaseNameHashValue;
/* 0x010c */ public: _LDR_DLL_LOAD_REASON LoadReason;
/* 0x0110 */ public: uint32_t ImplicitPathOptions;
/* 0x0114 */ public: uint32_t ReferenceCount;
/* 0x0118 */ public: uint32_t DependentLoadFlags;
/* 0x011c */ public: unsigned char SigningLevel;
/* 0x0120 */ public: uint32_t CheckSum;
/* 0x0128 */ public: void* ActivePatchImageBase;
/* 0x0130 */ public: _LDR_HOT_PATCH_STATE HotPatchState;
}LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

#endif