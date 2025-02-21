#pragma once

#ifndef _WIN64
#include "TEB32.h"
#else

#include "PEB.h"

typedef struct _TEB_ACTIVE_FRAME { /* Size=0x18 */
/* 0x0000 */ public: uint32_t Flags;
/* 0x0008 */ public: _TEB_ACTIVE_FRAME* Previous;
/* 0x0010 */ public: const void* Context;
}TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;

typedef struct _ACTIVATION_CONTEXT_STACK { /* Size=0x28 */
/* 0x0000 */ public: void* ActiveFrame;
/* 0x0008 */ public: _LIST_ENTRY FrameListCache;
/* 0x0018 */ public: uint32_t Flags;
/* 0x001c */ public: uint32_t NextCookieSequenceNumber;
/* 0x0020 */ public: uint32_t StackId;
}ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;

typedef struct _GDI_TEB_BATCH { /* Size=0x4e8 */
/* 0x0000 */ public: uint32_t Offset : 30; /* BitPos=0 */
/* 0x0000 */ public: uint32_t InProcessing : 1; /* BitPos=30 */
/* 0x0000 */ public: uint32_t HasRenderingCommand : 1; /* BitPos=31 */
/* 0x0008 */ public: uint64_t HDC;
/* 0x0010 */ public: uint32_t Buffer[310];
}GDI_TEB_BATCH, *PGDI_TEB_BATCH;

typedef struct _CLIENT_ID { /* Size=0x10 */
/* 0x0000 */ public: void* UniqueProcess;
/* 0x0008 */ public: void* UniqueThread;
}CLIENT_ID, *PCLIENT_ID;

typedef struct _TEB { /* Size=0x1878 */
/* 0x0000 */ public: _NT_TIB NtTib;
/* 0x0038 */ public: void* EnvironmentPointer;
/* 0x0040 */ public: _CLIENT_ID ClientId;
/* 0x0050 */ public: void* ActiveRpcHandle;
/* 0x0058 */ public: void* ThreadLocalStoragePointer;
/* 0x0060 */ public: _PEB* ProcessEnvironmentBlock;
/* 0x0068 */ public: uint32_t LastErrorValue;
/* 0x006c */ public: uint32_t CountOfOwnedCriticalSections;
/* 0x0070 */ public: void* CsrClientThread;
/* 0x0078 */ public: void* Win32ThreadInfo;
/* 0x0080 */ public: uint32_t User32Reserved[26];
/* 0x00e8 */ public: uint32_t UserReserved[5];
/* 0x0100 */ public: void* WOW32Reserved;
/* 0x0108 */ public: uint32_t CurrentLocale;
/* 0x010c */ public: uint32_t FpSoftwareStatusRegister;
/* 0x0110 */ public: void* ReservedForDebuggerInstrumentation[16];
/* 0x0190 */ public: void* SystemReserved1[25];
/* 0x0258 */ public: void* HeapFlsData;
/* 0x0260 */ public: uint64_t RngState[4];
/* 0x0280 */ public: char PlaceholderCompatibilityMode;
/* 0x0281 */ public: unsigned char PlaceholderHydrationAlwaysExplicit;
/* 0x0282 */ public: char PlaceholderReserved[10];
/* 0x028c */ public: uint32_t ProxiedProcessId;
/* 0x0290 */ public: _ACTIVATION_CONTEXT_STACK _ActivationStack;
/* 0x02b8 */ public: unsigned char WorkingOnBehalfTicket[8];
/* 0x02c0 */ public: int32_t ExceptionCode;
/* 0x02c4 */ public: unsigned char Padding0[4];
/* 0x02c8 */ public: _ACTIVATION_CONTEXT_STACK* ActivationContextStackPointer;
/* 0x02d0 */ public: uint64_t InstrumentationCallbackSp;
/* 0x02d8 */ public: uint64_t InstrumentationCallbackPreviousPc;
/* 0x02e0 */ public: uint64_t InstrumentationCallbackPreviousSp;
/* 0x02e8 */ public: uint32_t TxFsContext;
/* 0x02ec */ public: unsigned char InstrumentationCallbackDisabled;
/* 0x02ed */ public: unsigned char UnalignedLoadStoreExceptions;
/* 0x02ee */ public: unsigned char Padding1[2];
/* 0x02f0 */ public: _GDI_TEB_BATCH GdiTebBatch;
/* 0x07d8 */ public: _CLIENT_ID RealClientId;
/* 0x07e8 */ public: void* GdiCachedProcessHandle;
/* 0x07f0 */ public: uint32_t GdiClientPID;
/* 0x07f4 */ public: uint32_t GdiClientTID;
/* 0x07f8 */ public: void* GdiThreadLocalInfo;
/* 0x0800 */ public: uint64_t Win32ClientInfo[62];
/* 0x09f0 */ public: void* glDispatchTable[233];
/* 0x1138 */ public: uint64_t glReserved1[29];
/* 0x1220 */ public: void* glReserved2;
/* 0x1228 */ public: void* glSectionInfo;
/* 0x1230 */ public: void* glSection;
/* 0x1238 */ public: void* glTable;
/* 0x1240 */ public: void* glCurrentRC;
/* 0x1248 */ public: void* glContext;
/* 0x1250 */ public: uint32_t LastStatusValue;
/* 0x1254 */ public: unsigned char Padding2[4];
/* 0x1258 */ public: _UNICODE_STRING StaticUnicodeString;
/* 0x1268 */ public: wchar_t StaticUnicodeBuffer[261];
/* 0x1472 */ public: unsigned char Padding3[6];
/* 0x1478 */ public: void* DeallocationStack;
/* 0x1480 */ public: void* TlsSlots[64];
/* 0x1680 */ public: _LIST_ENTRY TlsLinks;
/* 0x1690 */ public: void* Vdm;
/* 0x1698 */ public: void* ReservedForNtRpc;
/* 0x16a0 */ public: void* DbgSsReserved[2];
/* 0x16b0 */ public: uint32_t HardErrorMode;
/* 0x16b4 */ public: unsigned char Padding4[4];
/* 0x16b8 */ public: void* Instrumentation[11];
/* 0x1710 */ public: _GUID ActivityId;
/* 0x1720 */ public: void* SubProcessTag;
/* 0x1728 */ public: void* PerflibData;
/* 0x1730 */ public: void* EtwTraceData;
/* 0x1738 */ public: void* WinSockData;
/* 0x1740 */ public: uint32_t GdiBatchCount;
                   union {
                   /* 0x1744 */ public: _PROCESSOR_NUMBER CurrentIdealProcessor;
                   /* 0x1744 */ public: uint32_t IdealProcessorValue;
                                      struct _{
                                      /* 0x1744 */ public: unsigned char ReservedPad0;
                                      /* 0x1745 */ public: unsigned char ReservedPad1;
                                      /* 0x1746 */ public: unsigned char ReservedPad2;
                                      /* 0x1747 */ public: unsigned char IdealProcessor;
                                      };
                   };
/* 0x1748 */ public: uint32_t GuaranteedStackBytes;
/* 0x174c */ public: unsigned char Padding5[4];
/* 0x1750 */ public: void* ReservedForPerf;
/* 0x1758 */ public: void* ReservedForOle;
/* 0x1760 */ public: uint32_t WaitingOnLoaderLock;
/* 0x1764 */ public: unsigned char Padding6[4];
/* 0x1768 */ public: void* SavedPriorityState;
/* 0x1770 */ public: uint64_t ReservedForCodeCoverage;
/* 0x1778 */ public: void* ThreadPoolData;
/* 0x1780 */ public: void** TlsExpansionSlots;
/* 0x1788 */ public: void* ChpeV2CpuAreaInfo;
/* 0x1790 */ public: void* Unused;
/* 0x1798 */ public: uint32_t MuiGeneration;
/* 0x179c */ public: uint32_t IsImpersonating;
/* 0x17a0 */ public: void* NlsCache;
/* 0x17a8 */ public: void* pShimData;
/* 0x17b0 */ public: uint32_t HeapData;
/* 0x17b4 */ public: unsigned char Padding7[4];
/* 0x17b8 */ public: void* CurrentTransactionHandle;
/* 0x17c0 */ public: _TEB_ACTIVE_FRAME* ActiveFrame;
/* 0x17c8 */ public: void* FlsData;
/* 0x17d0 */ public: void* PreferredLanguages;
/* 0x17d8 */ public: void* UserPrefLanguages;
/* 0x17e0 */ public: void* MergedPrefLanguages;
/* 0x17e8 */ public: uint32_t MuiImpersonation;
                   union {
                   /* 0x17ec */ public: volatile uint16_t CrossTebFlags;
                   /* 0x17ec */ public: uint16_t SpareCrossTebBits : 16; /* BitPos=0 */
                   };
                   union {
                   /* 0x17ee */ public: uint16_t SameTebFlags;
                                      struct _{
                                      /* 0x17ee */ public: uint16_t SafeThunkCall : 1; /* BitPos=0 */
                                      /* 0x17ee */ public: uint16_t InDebugPrint : 1; /* BitPos=1 */
                                      /* 0x17ee */ public: uint16_t HasFiberData : 1; /* BitPos=2 */
                                      /* 0x17ee */ public: uint16_t SkipThreadAttach : 1; /* BitPos=3 */
                                      /* 0x17ee */ public: uint16_t WerInShipAssertCode : 1; /* BitPos=4 */
                                      /* 0x17ee */ public: uint16_t RanProcessInit : 1; /* BitPos=5 */
                                      /* 0x17ee */ public: uint16_t ClonedThread : 1; /* BitPos=6 */
                                      /* 0x17ee */ public: uint16_t SuppressDebugMsg : 1; /* BitPos=7 */
                                      /* 0x17ee */ public: uint16_t DisableUserStackWalk : 1; /* BitPos=8 */
                                      /* 0x17ee */ public: uint16_t RtlExceptionAttached : 1; /* BitPos=9 */
                                      /* 0x17ee */ public: uint16_t InitialThread : 1; /* BitPos=10 */
                                      /* 0x17ee */ public: uint16_t SessionAware : 1; /* BitPos=11 */
                                      /* 0x17ee */ public: uint16_t LoadOwner : 1; /* BitPos=12 */
                                      /* 0x17ee */ public: uint16_t LoaderWorker : 1; /* BitPos=13 */
                                      /* 0x17ee */ public: uint16_t SkipLoaderInit : 1; /* BitPos=14 */
                                      /* 0x17ee */ public: uint16_t SkipFileAPIBrokering : 1; /* BitPos=15 */
                                      };
                   };
/* 0x17f0 */ public: void* TxnScopeEnterCallback;
/* 0x17f8 */ public: void* TxnScopeExitCallback;
/* 0x1800 */ public: void* TxnScopeContext;
/* 0x1808 */ public: uint32_t LockCount;
/* 0x180c */ public: int32_t WowTebOffset;
/* 0x1810 */ public: void* ResourceRetValue;
/* 0x1818 */ public: void* ReservedForWdf;
/* 0x1820 */ public: uint64_t ReservedForCrt;
/* 0x1828 */ public: _GUID EffectiveContainerId;
/* 0x1838 */ public: uint64_t LastSleepCounter;
/* 0x1840 */ public: uint32_t SpinCallCount;
/* 0x1844 */ public: unsigned char Padding8[4];
/* 0x1848 */ public: uint64_t ExtendedFeatureDisableMask;
/* 0x1850 */ public: void* SchedulerSharedDataSlot;
/* 0x1858 */ public: void* HeapWalkContext;
/* 0x1860 */ public: _GROUP_AFFINITY PrimaryGroupAffinity;
/* 0x1870 */ public: uint32_t Rcu[2];
}TEB, *PTEB;

#endif