#include "pch.h"
#include "LogManager.h"

LogManager::~LogManager()
{
    fclose(pStream);
    FreeConsole();
}

LogManager* LogManager::Get() noexcept
{
    static LogManager pLogManager;
    return &pLogManager;
}

bool LogManager::InitializeLogConsole() noexcept
{
    if(AllocConsole() == 0)
    {
        MessageBoxW(nullptr, L"Console Allocation Error", L"LogManager ERROR", MB_OKCANCEL | MB_ICONWARNING);
        return false;
    }

    if(freopen_s(&pStream, "CONOUT$", "w+", stdout) != 0)
    {
        MessageBoxW(nullptr, L"freopen_s Redirecting Stream Error", L"LogManager ERROR", MB_OKCANCEL | MB_ICONWARNING);
        return false;
    }

    pConsoleAppender = std::make_unique<plog::ConsoleAppender<plog::TxtFormatter>>();
    plog::init(plog::verbose, pConsoleAppender.get());

    return true;
}

bool LogManager::InitializeLogFile() noexcept
{
    //@TODO log to file, best place would be temp folder since we are internal
    return false;
}
