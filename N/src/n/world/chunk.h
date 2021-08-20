#pragma once
#include "pch.h"
#include "tile.h"
#include "sprite_batch.h"

namespace n
{
	template<typename T>
	class chunk_base : public mage::serializable
	{
	public:
		chunk_base(mage::input_file& in)
		{
			load(in);
		}
		N_DCM(chunk_base);
		virtual ~chunk_base() {}
	public:
		virtual void save(mage::output_file& out) const override
		{
			out.uint(m_coords.x).uint(m_coords.y);
		}
		virtual void load(mage::input_file& in) override
		{
			m_coords.x = in.uint();
			m_coords.y = in.uint();
		}
		template<typename SB, typename SAB>
		void draw(const mage::timestep& t, SB* const sb, const SAB* const ab, const shader_program& shader)
		{
			// draw all tiles in this chunk
			for (auto& batch : m_batches)
				batch->draw(t, sb, ab, shader);
		}
		glm::uvec2 get_pos() const
		{
			return m_coords;
		}
	protected:
		// in the editor, these are owned by a sprite_batch_bank, so don't delete them in the base dtor
		std::vector<T*> m_batches;
		glm::uvec2 m_coords;
	protected:
		chunk_base(const glm::uvec2& pos) :
			m_coords(pos)
		{}
	};



	class chunk final : public chunk_base<sprite_batch>
	{
	public:
		N_DCM(chunk);
		// batches are owned by each chunk in game builds
		~chunk()
		{
			for (auto& batch : m_batches)
				delete batch;
		}
	public:
		void save(mage::output_file& out) const override
		{
			MAGE_ASSERT(false, "Cannot save an n::chunk");
		}
		virtual void load(mage::input_file& in) override
		{
			m_coords.x = in.uint();
			m_coords.y = in.uint();

			const size_t batch_count = in.ulong();
			m_batches.reserve(batch_count);
			for (size_t i = 0; i < batch_count; i++)
				m_batches.push_back(new sprite_batch(in));
		}
	};
}
