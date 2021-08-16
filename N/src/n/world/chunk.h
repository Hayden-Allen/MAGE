#pragma once
#include "pch.h"
#include "tile.h"
#include "sprite_batch.h"

namespace n
{
	class chunk : public mage::serializable
	{
	public:
		chunk(mage::input_file& in) { load(in); }
		N_DCM(chunk);
		virtual ~chunk();
	public:
		virtual void save(mage::output_file& out) const override;
		virtual void load(mage::input_file& in) override;
		virtual void draw(const mage::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader);
	protected:
		std::vector<sprite_batch_base*> m_batches;
		glm::vec2 m_coords;
	protected:
		chunk() :
			m_coords({ 0.f, 0.f })
		{}
	};
}
