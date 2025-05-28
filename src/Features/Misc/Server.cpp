#include "pch.h"

#include "Server.hpp"

typedef struct addrinfo {
  int             ai_flags;
  int             ai_family;
  int             ai_socktype;
  int             ai_protocol;
  size_t          ai_addrlen;
  char            *ai_canonname;
  struct sockaddr *ai_addr;
  struct addrinfo *ai_next;
} ADDRINFOA, *PADDRINFOA;

typedef struct in6_addr {
    union {
        UCHAR  Byte[16];
        USHORT Word[8];
    } u;
} IN6_ADDR, * PIN6_ADDR, * LPIN6_ADDR;

struct sockaddr_in6 {
    short   sin6_family;
    u_short sin6_port;
    u_long  sin6_flowinfo;
    struct  in6_addr sin6_addr;
    u_long  sin6_scope_id;
};

static bool* pLogServerInfo = nullptr;

safetyhook::InlineHook getaddrinfo_hk;
INT __stdcall getaddrinfohk(PCSTR pNodeName,PCSTR pServiceName,const ADDRINFOA* pHints, PADDRINFOA* ppResult)
{
    if (pLogServerInfo && *pLogServerInfo)
    {
        static INT(__stdcall * pWSAAddressToStringA)
            (
                LPSOCKADDR lpsaAddress, DWORD dwAddressLength, void* lpProtocolInfo,
                LPSTR lpszAddressString, LPDWORD lpdwAddressStringLength
                )
            = reinterpret_cast<decltype(pWSAAddressToStringA)>(MadFramework::Memory::GetExport(L"Ws2_32.dll", "WSAAddressToStringA"));

        INT result = getaddrinfo_hk.stdcall<INT>(pNodeName, pServiceName, pHints, ppResult);

        if (pWSAAddressToStringA)
        {
            if (result == 0 && ppResult && *ppResult)
            {
                ADDRINFOA* p_addrinfo = *ppResult;

                while (p_addrinfo && p_addrinfo->ai_addr)
                {
                    DWORD dwSize = 46;
                    char resolved_ip[46];

                    const int addr_len = (p_addrinfo->ai_family == AF_INET) ? sizeof(sockaddr_in) : sizeof(sockaddr_in6);
                    pWSAAddressToStringA(p_addrinfo->ai_addr, addr_len, nullptr, resolved_ip, &dwSize);

                    PLOG_INFO << "IP: " << resolved_ip << " canonname: " << (p_addrinfo->ai_canonname ? p_addrinfo->ai_canonname : "");

                    p_addrinfo = p_addrinfo->ai_next;
                }
            }
        }

        return result;
    }

    return getaddrinfo_hk.stdcall<INT>(pNodeName, pServiceName, pHints, ppResult);
}

void HookServerConnectionInfo(bool& p_menu_state_flag)
{
    pLogServerInfo = &p_menu_state_flag;

    static bool init = false;

    if (!init)
    {
        void* p_getaddrinfo = MadFramework::Memory::GetExport(L"Ws2_32.dll", "getaddrinfo");
        getaddrinfo_hk = safetyhook::create_inline(p_getaddrinfo, getaddrinfohk);
        PLOG_INFO << "Hooked getaddrinfo: " << p_getaddrinfo;

        init = true;
    }
}

void RemoveServerConnectionHook()
{
    if (getaddrinfo_hk.enabled())
    {
        std::expected<void, safetyhook::InlineHook::Error> hook_status = getaddrinfo_hk.disable();

        if (!hook_status.has_value())
        {
            safetyhook::InlineHook::Error safetyError = hook_status.error();

            PLOG_ERROR << "Fatal Error unhooking getaddrinfo";
            PLOG_ERROR << "Error Type: " << safetyError.type;
            PLOG_ERROR << "IP: " << safetyError.ip;
        }
    }
}