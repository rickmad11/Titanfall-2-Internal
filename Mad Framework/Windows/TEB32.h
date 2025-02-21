#pragma once

#include "PEB32.h"

struct _GDI_TEB_BATCH { /* Size=0x4e0 */
/* 0x0000 */ public: uint32_t Offset : 30; /* BitPos=0 */
/* 0x0000 */ public: uint32_t InProcessing : 1; /* BitPos=30 */
/* 0x0000 */ public: uint32_t HasRenderingCommand : 1; /* BitPos=31 */
/* 0x0004 */ public: uint32_t HDC;
/* 0x0008 */ public: uint32_t Buffer[310];
};

struct _ACTIVATION_CONTEXT_STACK { /* Size=0x18 */
/* 0x0000 */ public: void* ActiveFrame;
/* 0x0004 */ public: _LIST_ENTRY FrameListCache;
/* 0x000c */ public: uint32_t Flags;
/* 0x0010 */ public: uint32_t NextCookieSequenceNumber;
/* 0x0014 */ public: uint32_t StackId;
};

struct _CLIENT_ID { /* Size=0x8 */
/* 0x0000 */ public: void* UniqueProcess;
/* 0x0004 */ public: void* UniqueThread;
};

struct _TEB { /* Size=0x1038 */
/* 0x0000 */ public: _NT_TIB NtTib;
/* 0x001c */ public: void* EnvironmentPointer;
/* 0x0020 */ public: _CLIENT_ID ClientId;
/* 0x0028 */ public: void* ActiveRpcHandle;
/* 0x002c */ public: void* ThreadLocalStoragePointer;
/* 0x0030 */ public: _PEB* ProcessEnvironmentBlock;
/* 0x0034 */ public: uint32_t LastErrorValue;
/* 0x0038 */ public: uint32_t CountOfOwnedCriticalSections;
/* 0x003c */ public: void* CsrClientThread;
/* 0x0040 */ public: void* Win32ThreadInfo;
/* 0x0044 */ public: uint32_t User32Reserved[26];
/* 0x00ac */ public: uint32_t UserReserved[5];
/* 0x00c0 */ public: void* WOW32Reserved;
/* 0x00c4 */ public: uint32_t CurrentLocale;
/* 0x00c8 */ public: uint32_t FpSoftwareStatusRegister;
/* 0x00cc */ public: void* ReservedForDebuggerInstrumentation[16];
/* 0x010c */ public: void* SystemReserved1[21];
/* 0x0160 */ public: void* HeapFlsData;
/* 0x0164 */ public: uint32_t RngState[4];
/* 0x0174 */ public: char PlaceholderCompatibilityMode;
/* 0x0175 */ public: unsigned char PlaceholderHydrationAlwaysExplicit;
/* 0x0176 */ public: char PlaceholderReserved[10];
/* 0x0180 */ public: uint32_t ProxiedProcessId;
/* 0x0184 */ public: _ACTIVATION_CONTEXT_STACK _ActivationStack;
/* 0x019c */ public: unsigned char WorkingOnBehalfTicket[8];
/* 0x01a4 */ public: int32_t ExceptionCode;
/* 0x01a8 */ public: _ACTIVATION_CONTEXT_STACK* ActivationContextStackPointer;
/* 0x01ac */ public: uint32_t InstrumentationCallbackSp;
/* 0x01b0 */ public: uint32_t InstrumentationCallbackPreviousPc;
/* 0x01b4 */ public: uint32_t InstrumentationCallbackPreviousSp;
/* 0x01b8 */ public: unsigned char InstrumentationCallbackDisabled;
/* 0x01b9 */ public: unsigned char SpareBytes[23];
/* 0x01d0 */ public: uint32_t TxFsContext;
/* 0x01d4 */ public: _GDI_TEB_BATCH GdiTebBatch;
/* 0x06b4 */ public: _CLIENT_ID RealClientId;
/* 0x06bc */ public: void* GdiCachedProcessHandle;
/* 0x06c0 */ public: uint32_t GdiClientPID;
/* 0x06c4 */ public: uint32_t GdiClientTID;
/* 0x06c8 */ public: void* GdiThreadLocalInfo;
/* 0x06cc */ public: uint32_t Win32ClientInfo[62];
/* 0x07c4 */ public: void* glDispatchTable[233];
/* 0x0b68 */ public: uint32_t glReserved1[29];
/* 0x0bdc */ public: void* glReserved2;
/* 0x0be0 */ public: void* glSectionInfo;
/* 0x0be4 */ public: void* glSection;
/* 0x0be8 */ public: void* glTable;
/* 0x0bec */ public: void* glCurrentRC;
/* 0x0bf0 */ public: void* glContext;
/* 0x0bf4 */ public: uint32_t LastStatusValue;
/* 0x0bf8 */ public: _UNICODE_STRING StaticUnicodeString;
/* 0x0c00 */ public: wchar_t StaticUnicodeBuffer[261];
/* 0x0e0c */ public: void* DeallocationStack;
/* 0x0e10 */ public: void* TlsSlots[64];
/* 0x0f10 */ public: _LIST_ENTRY TlsLinks;
/* 0x0f18 */ public: void* Vdm;
/* 0x0f1c */ public: void* ReservedForNtRpc;
/* 0x0f20 */ public: void* DbgSsReserved[2];
/* 0x0f28 */ public: uint32_t HardErrorMode;
/* 0x0f2c */ public: void* Instrumentation[9];
/* 0x0f50 */ public: _GUID ActivityId;
/* 0x0f60 */ public: void* SubProcessTag;
/* 0x0f64 */ public: void* PerflibData;
/* 0x0f68 */ public: void* EtwTraceData;
/* 0x0f6c */ public: void* WinSockData;
/* 0x0f70 */ public: uint32_t GdiBatchCount;
                   union {
                   /* 0x0f74 */ public: _PROCESSOR_NUMBER CurrentIdealProcessor;
                   /* 0x0f74 */ public: uint32_t IdealProcessorValue;
                                      struct _{
                                      /* 0x0f74 */ public: unsigned char ReservedPad0;
                                      /* 0x0f75 */ public: unsigned char ReservedPad1;
                                      /* 0x0f76 */ public: unsigned char ReservedPad2;
                                      /* 0x0f77 */ public: unsigned char IdealProcessor;
                                      };
                   };
/* 0x0f78 */ public: uint32_t GuaranteedStackBytes;
/* 0x0f7c */ public: void* ReservedForPerf;
/* 0x0f80 */ public: void* ReservedForOle;
/* 0x0f84 */ public: uint32_t WaitingOnLoaderLock;
/* 0x0f88 */ public: void* SavedPriorityState;
/* 0x0f8c */ public: uint32_t ReservedForCodeCoverage;
/* 0x0f90 */ public: void* ThreadPoolData;
/* 0x0f94 */ public: void** TlsExpansionSlots;
/* 0x0f98 */ public: uint32_t MuiGeneration;
/* 0x0f9c */ public: uint32_t IsImpersonating;
/* 0x0fa0 */ public: void* NlsCache;
/* 0x0fa4 */ public: void* pShimData;
/* 0x0fa8 */ public: uint32_t HeapData;
/* 0x0fac */ public: void* CurrentTransactionHandle;
/* 0x0fb0 */ public: void* ActiveFrame;
/* 0x0fb4 */ public: void* FlsData;
/* 0x0fb8 */ public: void* PreferredLanguages;
/* 0x0fbc */ public: void* UserPrefLanguages;
/* 0x0fc0 */ public: void* MergedPrefLanguages;
/* 0x0fc4 */ public: uint32_t MuiImpersonation;
                   union {
                   /* 0x0fc8 */ public: volatile uint16_t CrossTebFlags;
                   /* 0x0fc8 */ public: uint16_t SpareCrossTebBits : 16; /* BitPos=0 */
                   };
                   union {
                   /* 0x0fca */ public: uint16_t SameTebFlags;
                                      struct _{
                                      /* 0x0fca */ public: uint16_t SafeThunkCall : 1; /* BitPos=0 */
                                      /* 0x0fca */ public: uint16_t InDebugPrint : 1; /* BitPos=1 */
                                      /* 0x0fca */ public: uint16_t HasFiberData : 1; /* BitPos=2 */
                                      /* 0x0fca */ public: uint16_t SkipThreadAttach : 1; /* BitPos=3 */
                                      /* 0x0fca */ public: uint16_t WerInShipAssertCode : 1; /* BitPos=4 */
                                      /* 0x0fca */ public: uint16_t RanProcessInit : 1; /* BitPos=5 */
                                      /* 0x0fca */ public: uint16_t ClonedThread : 1; /* BitPos=6 */
                                      /* 0x0fca */ public: uint16_t SuppressDebugMsg : 1; /* BitPos=7 */
                                      /* 0x0fca */ public: uint16_t DisableUserStackWalk : 1; /* BitPos=8 */
                                      /* 0x0fca */ public: uint16_t RtlExceptionAttached : 1; /* BitPos=9 */
                                      /* 0x0fca */ public: uint16_t InitialThread : 1; /* BitPos=10 */
                                      /* 0x0fca */ public: uint16_t SessionAware : 1; /* BitPos=11 */
                                      /* 0x0fca */ public: uint16_t LoadOwner : 1; /* BitPos=12 */
                                      /* 0x0fca */ public: uint16_t LoaderWorker : 1; /* BitPos=13 */
                                      /* 0x0fca */ public: uint16_t SkipLoaderInit : 1; /* BitPos=14 */
                                      /* 0x0fca */ public: uint16_t SkipFileAPIBrokering : 1; /* BitPos=15 */
                                      };
                   };
/* 0x0fcc */ public: void* TxnScopeEnterCallback;
/* 0x0fd0 */ public: void* TxnScopeExitCallback;
/* 0x0fd4 */ public: void* TxnScopeContext;
/* 0x0fd8 */ public: uint32_t LockCount;
/* 0x0fdc */ public: int32_t WowTebOffset;
/* 0x0fe0 */ public: void* ResourceRetValue;
/* 0x0fe4 */ public: void* ReservedForWdf;
/* 0x0fe8 */ public: uint64_t ReservedForCrt;
/* 0x0ff0 */ public: _GUID EffectiveContainerId;
/* 0x1000 */ public: uint64_t LastSleepCounter;
/* 0x1008 */ public: uint32_t SpinCallCount;
/* 0x1010 */ public: uint64_t ExtendedFeatureDisableMask;
/* 0x1018 */ public: void* SchedulerSharedDataSlot;
/* 0x101c */ public: void* HeapWalkContext;
/* 0x1020 */ public: _GROUP_AFFINITY PrimaryGroupAffinity;
/* 0x102c */ public: uint32_t Rcu[2];
};
