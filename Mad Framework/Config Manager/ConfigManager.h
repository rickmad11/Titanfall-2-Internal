#pragma once

class ConfigManager final
{
public:
	ConfigManager(LogManager const&) = delete;
	ConfigManager& operator=(ConfigManager const&) = delete;

	ConfigManager(ConfigManager&&) = delete;
	ConfigManager& operator=(ConfigManager&&) = delete;

private:
	ConfigManager() = default;
	~ConfigManager() = default;

public:
	static ConfigManager* Get() noexcept;
	std::vector<std::string> GetAllConfigs() noexcept;
	std::string GetCurrentConfigFile() const noexcept;
	bool IsValid() const noexcept;
	void UpdateConfigFile(const char* config_file_name) noexcept;
	void RemoveConfigFile() const noexcept;
	bool InitializeConfigManager(std::string_view file_name);
	bool HasFailed();
	void AddValue(std::string_view header, std::string_view name, auto value);
	void GetValue(std::string_view header, std::string_view name, auto& value);
	void ResetFile();
	void Begin();
	void End();

public:
	inline static const std::string default_string { "RM11_TF2_Config.ini" };

private:
	std::string ini_file_name{};
	std::filesystem::path app_data_file_path {};
	std::filesystem::path ini_file_path{};
	mINI::INIStructure ini_file_data{};
	bool failure = false;
};

void ConfigManager::AddValue(std::string_view header, std::string_view name, auto value)
{
	ini_file_data[header.data()][name.data()] = std::to_string(value);
}

void ConfigManager::GetValue(std::string_view header, std::string_view name, auto& value)
{
	using ValueType = std::decay_t<decltype(value)>;

	if (!ini_file_data.has(header.data()) || !ini_file_data[header.data()].has(name.data()))
		return;

	if constexpr (std::is_integral_v<ValueType>)
		value = static_cast<ValueType>(std::stoll(ini_file_data[header.data()][name.data()]));
	else if constexpr (std::is_floating_point_v<ValueType>)
		value = static_cast<ValueType>(std::stod(ini_file_data[header.data()][name.data()]));
	else if constexpr  (std::is_enum_v<ValueType>)
		value = static_cast<ValueType>(std::stoll(ini_file_data[header.data()][name.data()]));

	//value = static_cast<std::remove_reference_t<decltype(value)>>(std::stoll(ini_file_data[header.data()][name.data()]));
}