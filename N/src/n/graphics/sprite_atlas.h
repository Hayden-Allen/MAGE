#pragma once
#include "pch.h"
#include "wrap/texture.h"

namespace n
{
	struct sprite_atlas_coords
	{
		mage::range<float> x = { 0.f, 1.f }, y = { 0.f, 1.f };
		void operator=(const sprite_atlas_coords& other)
		{
			x = other.x;
			y = other.y;
		}
	};



	class sprite_atlas final : public mage::dimensional3<uint32_t>
	{
	public:
		sprite_atlas();
		MAGE_DCM(sprite_atlas);
		~sprite_atlas()
		{
			delete m_texture;
		}


		void bind(uint32_t slot) const
		{
			m_texture->bind(slot);
		}
		sprite_atlas_coords insert(s_type w, s_type h, s_type frames, const uint8_t* const data);
	private:
		texture2d_array* m_texture;
	};
}
