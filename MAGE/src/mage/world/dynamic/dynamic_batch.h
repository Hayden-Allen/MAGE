#pragma once
#include "pch.h"
#include "dynamic_batch_list.h"

namespace mage
{
	class sprite;
	class dynamic_list;

	class dynamic_batch : public coga::indexed_list<size_t, size_t, size_t, size_t>
	{
		friend class dynamic_list;
	public:
		dynamic_batch();
		COGA_DCM(dynamic_batch);
		~dynamic_batch()
		{
			delete m_indices;
		}
	public:
		size_t add(size_t dynamic) override;
		void remove(size_t dynamic) override;
		void move(dynamic_list& list, float dt) const;
		void draw(dynamic_list& list) const;
	private:
		dynamic_batch_list::handle m_index;
		COGA_RAN::dynamic_index_buffer* m_indices;
		mutable std::vector<sprite*> m_sprites;
	};
}
