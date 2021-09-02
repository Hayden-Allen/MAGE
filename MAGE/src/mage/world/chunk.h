#pragma once
#include "pch.h"
#include "tile.h"
#include "sprite_batch.h"

namespace mage
{
	template<typename T>
	class chunk_base : public coga::serializable
	{
	public:
		chunk_base(coga::input_file& in)
		{
			load(in);
		}
		MAGE_DCM(chunk_base);
		virtual ~chunk_base() {}
	public:
		virtual void save(coga::output_file& out) const override
		{
			out.uint(m_coords.x).uint(m_coords.y);
		}
		virtual void load(coga::input_file& in) override
		{
			m_coords.x = in.uint();
			m_coords.y = in.uint();
		}
		template<typename SB, typename SAB>
		void draw(const coga::timestep& t, SB* const sb, const SAB* const ab, const shader_program& shader)
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
		MAGE_DCM(chunk);
		// batches are owned by each chunk in game builds
		~chunk()
		{
			for (auto& batch : m_batches)
				delete batch;
		}
	public:
		void save(coga::output_file& out) const override
		{
			COGA_ASSERT(false, "Cannot save an mage::chunk");
		}
		virtual void load(coga::input_file& in) override
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
