#pragma once

class LogManager final
{
public:
	LogManager(LogManager const&) = delete;
	LogManager& operator=(LogManager const&) = delete;

	LogManager(LogManager&&) = delete;
	LogManager& operator=(LogManager&&) = delete;

private:
	LogManager() = default;
	~LogManager();

public:
	static LogManager* Get() noexcept;
	bool InitializeLogConsole() noexcept;
	bool InitializeLogFile() noexcept;

private:
	FILE* pStream = nullptr;
	std::unique_ptr<plog::ConsoleAppender<plog::TxtFormatter>> pConsoleAppender = nullptr;
};

