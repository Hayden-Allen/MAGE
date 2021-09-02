#pragma once
#include "pch.h"
#include "dynamic_batch_list.h"

namespace mage
{
	class dynamic;

	struct dynamic_list_handle
	{
		size_t list, batch, texture;
	};

	class dynamic_list : public coga::indexed_list<dynamic*, dynamic_list_handle, dynamic* const, dynamic* const>
	{
		friend class dynamic_batch;
	public:
		dynamic_list();
		MAGE_DCM(dynamic_list);
		~dynamic_list();
	public:
		dynamic_list_handle add(dynamic* const d) override;
		void remove(dynamic* const d) override;
		void draw();
		void update(float dt);
		void update_one(size_t i);
	private:
		COGA_RAN::dynamic_vertex_buffer* m_vertex_buffer;
		COGA_RAN::dynamic_vertex_array* m_vertex_array;
		dynamic_batch_list m_batches;
	};
}
