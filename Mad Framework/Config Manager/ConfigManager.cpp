#include "pch.h"

#include "ConfigManager.h"

ConfigManager* ConfigManager::Get() noexcept
{
	static ConfigManager pConfigManager;
	return &pConfigManager;
}

std::vector<std::string> ConfigManager::GetAllConfigs() noexcept
{
	std::vector<std::string> configs;

	if (std::filesystem::exists(app_data_file_path))
	{
		for (const auto& file : std::filesystem::directory_iterator(app_data_file_path))
			if (file.path().extension() == ".ini")
				configs.push_back(file.path().filename().string());
	}

	return configs;
}

std::string ConfigManager::GetCurrentConfigFile() const noexcept
{
	return ini_file_path.string();
}

bool ConfigManager::IsValid() const noexcept
{
	return std::filesystem::file_size(ini_file_path);
}

void ConfigManager::UpdateConfigFile(const char* config_file_name) noexcept
{
	if (config_file_name)
		ini_file_path = app_data_file_path / std::string{ config_file_name };
}

void ConfigManager::RemoveConfigFile() const noexcept
{
	std::filesystem::remove(ini_file_path);
}

bool ConfigManager::InitializeConfigManager(std::string_view file_name)
{
	if (file_name == ini_file_name)
		return true;

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
		static std::once_flag flag;
		std::call_once(flag, []{ PLOG_INFO << "Config file found"; });
		return true;
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

bool ConfigManager::ValueExists(std::string_view header, std::string_view name)
{
	return ini_file_data.has(header.data()) && ini_file_data[header.data()].has(name.data());
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
