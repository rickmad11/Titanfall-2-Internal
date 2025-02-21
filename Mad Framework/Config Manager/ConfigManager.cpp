#include "pch.h"

#include "ConfigManager.h"

ConfigManager* ConfigManager::Get() noexcept
{
	static ConfigManager pConfigManager;
	return &pConfigManager;
}

bool ConfigManager::InitializeConfigManager(std::string_view file_name)
{
	ini_file_name = file_name;

	WCHAR path[MAX_PATH] {};
	HRESULT result = SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, GetCurrentProcessToken(), SHGFP_TYPE_CURRENT, path);

	if(result != S_OK)
	{
		PLOG_ERROR << "Failed getting local AppData path";
		PLOG_WARNING << "The Config file cannot be found or created, you can ignore this if you don't care about saving your settings";
		failure = true;
		return false;
	}

	app_data_file_path = std::filesystem::path{ path } / "RM11 Configs";
	ini_file_path = app_data_file_path / ini_file_name;

	if(std::filesystem::exists(ini_file_path))
	{
		PLOG_INFO << "Config filed found";
		return false;
	}

	if(!std::filesystem::exists(app_data_file_path))
	{
		std::filesystem::create_directory(app_data_file_path);
		PLOG_INFO << "Created folder at: " << app_data_file_path;
	}

	mINI::INIFile ini_file { ini_file_path.string() };

	if(!ini_file.generate(ini_file_data, true))
	{
		PLOG_ERROR << "Failed Creating Ini File";
		PLOG_WARNING << "The Config file cannot be found or created, you can ignore this if you don't care about saving your settings";
		failure = true;
		return false;
	}
	
	PLOG_INFO << "Config file created at: " << ini_file_path;

	return true;
}

bool ConfigManager::HasFailed()
{
	return failure;
}

void ConfigManager::ResetFile()
{
	ini_file_data = {};
	mINI::INIFile ini_file{ ini_file_path.string() };
	(void)ini_file.generate(ini_file_data, true);
}

void ConfigManager::Begin()
{
	mINI::INIFile ini_file{ ini_file_path.string() };
	ini_file.read(ini_file_data);
}

void ConfigManager::End()
{
	mINI::INIFile ini_file{ ini_file_path.string() };
	ini_file.write(ini_file_data);
	ini_file_data = {};
}
