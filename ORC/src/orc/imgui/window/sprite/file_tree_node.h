#pragma once
#include "pch.h"

namespace orc
{
	class sprite;
	class sprite_bank;
	class sprite_atlas_bank;

	class file_tree_node
	{
	public:
		file_tree_node(const std::string& name, sprite_bank* sb, sprite_atlas_bank* ab, file_tree_node* parent = nullptr);
		COGA_DCM(file_tree_node);
		virtual ~file_tree_node();
	public:
		void add_file(std::string path);
		void remove_file(const std::string& name);
		void remove_folder(const std::string& name);
		sprite* draw() const;
		bool has_files() const
		{
			return !m_files.empty();
		}
		bool is_empty() const
		{
			return m_files.empty() && m_folders.empty();
		}
	private:
		constexpr static char s_separator_token = '/', s_extension_token = '.', s_valid_extension[] = "sprite";
		constexpr static ImGuiTreeNodeFlags s_imgui_flags =
			ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
		const static inline ImVec4 s_folder_color = { .8f, .8f, .8f, 1.f }, s_file_color = { 1.f, 1.f, 1.f, 1.f };
	private:
		file_tree_node* m_parent;
		std::string m_name;
		std::map<std::string, sprite*> m_files;
		std::map<std::string, file_tree_node*> m_folders;
		sprite_bank* m_sprite_bank;
		sprite_atlas_bank* m_atlas_bank;
	private:
		void add_file(const std::string& path, const std::string& stub);
		sprite* draw(std::string path, int* id) const;
	};
}
