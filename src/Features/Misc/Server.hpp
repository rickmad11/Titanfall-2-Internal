#pragma once

void HookServerConnectionInfo(bool& p_menu_state_flag, bool& p_menu_state_button_flag);
void RemoveServerConnectionHook();
void SendClientMessage(const std::string_view message);