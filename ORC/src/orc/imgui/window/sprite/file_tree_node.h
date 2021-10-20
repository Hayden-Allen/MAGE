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
		file_tree_node* m_parent;
		std::string m_name;
		std::map<std::string, sprite*> m_files;
		std::map<std::string, file_tree_node*> m_folders;
		sprite_bank* m_sprite_bank;
		sprite_atlas_bank* m_atlas_bank;
	private:
		file_tree_node(file_tree_node* parent, const std::string& name, const std::map<std::string, sprite*>& files, const std::map<std::string, file_tree_node*>& folders, sprite_bank* sb, sprite_atlas_bank* ab) :
			m_parent(parent),
			m_name(name),
			m_files(files),
			m_folders(folders),
			m_sprite_bank(sb),
			m_atlas_bank(ab)
		{}
		file_tree_node(const file_tree_node* other) :
			m_parent(other->m_parent),
			m_name(other->m_name),
			m_files(other->m_files),
			m_sprite_bank(other->m_sprite_bank),
			m_atlas_bank(other->m_atlas_bank)
		{
			// deep copy
			for (const auto& pair : other->m_folders)
				m_folders.insert({ pair.first, new file_tree_node(pair.second) });
		}
	private:
		void add_file(const std::string& path, const std::string& stub);
		sprite* draw(std::string path, int* id) const;
		static void clean_path(std::string& s)
		{
			std::replace_if(s.begin(), s.end(), [](char c) { return c == '\\'; }, c::file_tree_separator_token);
		}
	};
}
