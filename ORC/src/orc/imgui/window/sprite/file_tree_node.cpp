#include "pch.h"
#include "file_tree_node.h"
#include "orc/graphics/sprite.h"
#include "orc/graphics/sprite_bank.h"
#include "orc/graphics/sprite_atlas_bank.h"

namespace orc
{
	file_tree_node::file_tree_node(const std::string& name, sprite_bank* sb, sprite_atlas_bank* ab, file_tree_node* parent) :
		m_parent(parent),
		m_name(name),
		m_sprite_bank(sb),
		m_atlas_bank(ab)
	{}
	file_tree_node::~file_tree_node()
	{
		for (const auto& pair : m_folders)
			delete pair.second;
	}



	void file_tree_node::add_file(std::string path)
	{
		clean_path(path);
		add_file(path, path);
	}
	void file_tree_node::remove_file(const std::string& name)
	{
		if (!m_files.contains(name))
			COGA_ERROR("Cannot remove non-existent sprite '%s'", name.c_str());
		else
			m_files.erase(name);

		// parent owns its children
		if (is_empty())
			m_parent->remove_folder(m_name);
	}
	void file_tree_node::remove_folder(const std::string& name)
	{
		const auto& it = m_folders.find(name);
		if (it == m_folders.end())
			COGA_ERROR("Cannot remove non-existent folder '%s'", name.c_str());
		else
		{
			// parents own their children
			delete it->second;
			m_folders.erase(it);
		}
	}
	sprite* file_tree_node::draw() const
	{
		int id = 0;
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10.f);
		sprite* selected = draw(m_name, &id);
		ImGui::PopStyleVar();
		return selected;
	}



	void file_tree_node::add_file(const std::string& path, const std::string& stub)
	{
		const size_t separator_index = stub.find_first_of(c::file_tree_separator_token);
		// this is the terminal node
		if (separator_index == std::string::npos)
		{
			const size_t type_index = stub.find_first_of(c::file_tree_extension_token);
			// no or invalid file extension
			if (type_index == std::string::npos || stub.substr(type_index + 1) != c::file_tree_valid_extension)
			{
				COGA_ERROR("Only '.sprite' files can be added");
				return;
			}

			const std::string name = stub.substr(0, type_index);
			// this node already contains a file with the same name
			if (m_files.contains(name))
				COGA_WARN("Overwriting sprite file '%s'", name.c_str());
			m_files.insert({ name, new sprite(m_sprite_bank, m_atlas_bank, path) });
		}
		// this is a non-terminal node
		else
		{
			const std::string name = stub.substr(0, separator_index);
			file_tree_node* next = nullptr;

			const auto& it = m_folders.find(name);
			// subfolder already exists
			if (it != m_folders.end())
				next = it->second;
			// subfolder doesn't exist; create and add it
			else
			{
				next = new file_tree_node(name, m_sprite_bank, m_atlas_bank, this);
				m_folders.insert({ name, next });
			}
			next->add_file(path, stub.substr(separator_index + 1));
		}
	}
	sprite* file_tree_node::draw(std::string path, int* id) const
	{
		// the currently selected sprite
		sprite* result = nullptr;
		ImGui::PushID(*id++);

		// if this node is open
		ImGui::PushStyleColor(ImGuiCol_Text, c::file_tree_folder_color);
		if (ImGui::TreeNodeEx(m_name.c_str(), has_files() ? ImGuiTreeNodeFlags_None : ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::PopStyleColor();
			for (const auto& pair : m_folders)
				result = pair.second->draw(path, id);
			ImGui::PushStyleColor(ImGuiCol_Text, c::file_tree_file_color);
			for (const auto& pair : m_files)
			{
				ImGui::PushID(*id++);

				ImGui::TreeNodeEx(pair.first.c_str(), c::file_tree_imgui_flags);
				// this is the currently selected sprite
				if (ImGui::IsItemClicked())
					result = pair.second;
				// for some reason this crashes
				// ImGui::TreePop();

				ImGui::PopID();
			}
			ImGui::PopStyleColor();
			ImGui::TreePop();
		}
		// this needs to be popped regardless of if the node is open
		else
			ImGui::PopStyleColor();

		ImGui::PopID();
		return result;
	}
}
