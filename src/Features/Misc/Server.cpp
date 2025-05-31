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
static bool* pLogServerInfoButton = nullptr;

safetyhook::InlineHook ih_getaddrinfo_hk;
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

        INT result = ih_getaddrinfo_hk.stdcall<INT>(pNodeName, pServiceName, pHints, ppResult);

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

                    PLOG_INFO << "Game Main Server IP: " << resolved_ip;
                    //PLOG_INFO << "IP: " << resolved_ip << " canonname: " << (p_addrinfo->ai_canonname ? p_addrinfo->ai_canonname : "");

                    p_addrinfo = p_addrinfo->ai_next;
                }
            }
        }

        return result;
    }

    return ih_getaddrinfo_hk.stdcall<INT>(pNodeName, pServiceName, pHints, ppResult);
}

//u_short GetPortFromString()
//{
//    //[::ffff:18.184.189.194]:37016
//
//    std::size_t pos = server_ip.find_last_of(':');
//    if (pos == std::string::npos)
//        return 0;
//
//    return static_cast<u_short>(std::atoi(server_ip.substr(pos + 1).c_str()));
//}
//
//std::string GetIpFromString()
//{
//    std::size_t pos_start = server_ip.find("::ffff:");
//
//    if (pos_start == std::string::npos)
//        return "";
//
//    std::size_t pos_end = server_ip.find(']', pos_start + 7);
//
//    if (pos_end == std::string::npos)
//        return "";
//
//    return server_ip.substr(pos_start + 7, pos_end - (pos_start + 7));
//}

static std::string server_ip;

std::pair <std::string, int> GetServerData()
{
    std::regex pattern(R"(\[::ffff:([\d\.]+)\]:(\d+))");
    std::smatch match;

    if (std::regex_match(server_ip, match, pattern))
    {
        std::string ip = match[1];
        int port = std::stoi(match[2]);
        return { ip, port };
    }

    return { "", -1 };
}

safetyhook::InlineHook ih_sendto_hk;
int sendto_hk(SOCKET socket, const char* buf, int len, int flags, const sockaddr* to, int tolen)
{
    static INT(__stdcall * pWSAAddressToStringA)
        (
            LPSOCKADDR lpsaAddress, DWORD dwAddressLength, void* lpProtocolInfo,
            LPSTR lpszAddressString, LPDWORD lpdwAddressStringLength
            )
        = reinterpret_cast<decltype(pWSAAddressToStringA)>(MadFramework::Memory::GetExport(L"Ws2_32.dll", "WSAAddressToStringA"));

    if (*pLogServerInfoButton && pWSAAddressToStringA && to && buf)
    {
        DWORD dwSize = 46;
        char resolved_ip[46];

        const int addr_len = (to->sa_family == AF_INET) ? sizeof(sockaddr_in) : sizeof(sockaddr_in6);
        pWSAAddressToStringA(const_cast<sockaddr*>(to), addr_len, nullptr, resolved_ip, &dwSize);

        server_ip = resolved_ip;

        auto [ip, port] = GetServerData();

        PLOG_INFO << "Current Server IP: " << ip << " Port: " << port;

        *pLogServerInfoButton = false;
    }

    return ih_sendto_hk.stdcall<int>(socket, buf, len, flags, to, tolen);
}

void HookServerConnectionInfo(bool& p_menu_state_flag, bool& p_menu_state_button_flag)
{
    pLogServerInfo = &p_menu_state_flag;
    pLogServerInfoButton = &p_menu_state_button_flag;

    static bool init = false;

    if (!init)
    {
        void* p_getaddrinfo = MadFramework::Memory::GetExport(L"Ws2_32.dll", "getaddrinfo");
        ih_getaddrinfo_hk = safetyhook::create_inline(p_getaddrinfo, getaddrinfohk);
        PLOG_INFO << "Hooked getaddrinfo in Ws2_32.dll: " << p_getaddrinfo;

        void* p_sendto = MadFramework::Memory::GetExport(L"Ws2_32.dll", "sendto");
        ih_sendto_hk = safetyhook::create_inline(p_sendto, sendto_hk);
        PLOG_INFO << "Hooked sendto in Ws2_32.dll: " << p_sendto;

        init = true;
    }
}

void RemoveServerConnectionHook()
{
    if (ih_getaddrinfo_hk.enabled())
    {
        std::expected<void, safetyhook::InlineHook::Error> hook_status = ih_getaddrinfo_hk.disable();

        if (!hook_status.has_value())
        {
            safetyhook::InlineHook::Error safetyError = hook_status.error();

            PLOG_ERROR << "Fatal Error unhooking getaddrinfo";
            PLOG_ERROR << "Error Type: " << safetyError.type;
            PLOG_ERROR << "IP: " << safetyError.ip;
        }
    }

    if (ih_sendto_hk.enabled())
    {
        std::expected<void, safetyhook::InlineHook::Error> hook_status = ih_sendto_hk.disable();

        if (!hook_status.has_value())
        {
            safetyhook::InlineHook::Error safetyError = hook_status.error();

            PLOG_ERROR << "Fatal Error unhooking sendto";
            PLOG_ERROR << "Error Type: " << safetyError.type;
            PLOG_ERROR << "IP: " << safetyError.ip;
        }
    }
}