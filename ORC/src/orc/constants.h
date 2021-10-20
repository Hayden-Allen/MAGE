#pragma once
#include "pch.h"

namespace orc::c
{
	constexpr static char game_window_title[] = "Game";
	constexpr static char debug_window_title[] = "Debug";
	constexpr static char sprite_window_title[] = "Sprites";

	constexpr static char dockspace_title[] = "Dockspace";
	constexpr static char dockspace_id[] = "__orc_dockspace_id";

	constexpr static char file_tree_separator_token = '/', file_tree_extension_token = '.', file_tree_valid_extension[] = "sprite";
	constexpr static ImGuiTreeNodeFlags file_tree_imgui_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
	const static inline ImVec4 file_tree_folder_color = { .8f, .8f, .8f, 1.f }, file_tree_file_color = { 1.f, 1.f, 1.f, 1.f };
}
