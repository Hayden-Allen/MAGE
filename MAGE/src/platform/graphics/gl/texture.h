#pragma once
#include "pch.h"
#include "mage/graphics/texture.h"

namespace mage::gl
{
	template<GLenum T>
	class texture : public mage::gfx::texture
	{
	public:
		MAGE_DCM(texture);
		virtual ~texture();


		void bind(uint32_t slot) const override
		{
			// max is GL_TEXTURE31
			MAGE_CORE_ASSERT(slot < 32, "Invalid OpenGL texture slot");
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(T, m_id);
		}
		void unbind() const override
		{
			glBindTexture(T, 0);
		}
	protected:
		texture(s_type w, s_type h, void* data);
	};



#define T(NAME, TYPE, SIG) \
	class NAME : public texture<TYPE>, public mage::gfx::NAME { \
	public: \
		using texture<TYPE>::m_id; \
		NAME SIG; \
		MAGE_DCM(NAME); \
		mage::gfx::renderer_id_t get_id() const override { return texture<TYPE>::m_id; } \
		void bind(uint32_t slot) const { texture<TYPE>::bind(slot); } \
		void unbind() const override { texture<TYPE>::unbind(); } };

	T(texture2d, GL_TEXTURE_2D, (s_type w, s_type h, void* data));
	T(texture2d_array, GL_TEXTURE_2D_ARRAY, (s_type w, s_type h, s_type f, void* data));

#undef T
}
