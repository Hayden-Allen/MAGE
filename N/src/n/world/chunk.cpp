#include "pch.h"
#include "chunk.h"

namespace n
{
	chunk::~chunk()
	{
		for (auto& batch : m_batches)
			delete batch;
	}



	void chunk::save(mage::output_file& out) const
	{
		out.uint(m_coords.x).uint(m_coords.y);
		out.ulong(m_batches.size());
		for (const auto& batch : m_batches)
			batch->save(out);
	}
	void chunk::load(mage::input_file& in)
	{
		m_coords.x = in.uint();
		m_coords.y = in.uint();

		const size_t batch_count = in.ulong();
		m_batches.reserve(batch_count);
		for (size_t i = 0; i < batch_count; i++)
			m_batches.push_back(new sprite_batch(in));
	}
	void chunk::draw(const mage::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader)
	{
		// draw all tiles in this chunk
		for (auto& batch : m_batches)
			batch->draw(t, sb, ab, shader);
	}
}
