#pragma once
#include "pch.h"
#include "texture_options.h"
#include "mage/graphics/texture.h"

namespace mage::gl
{
#define T(NAME, TYPE, SIG, UPDATE) \
	class NAME : public mage::gfx::NAME { \
	public: \
		NAME SIG; \
		MAGE_DCM(NAME); \
		~NAME() { glDeleteTextures(1, &m_id); } \
		void bind(uint32_t slot) const { MAGE_CORE_ASSERT(slot < 32, "Invalid OpenGL texture slot"); glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(TYPE, m_id); } \
		void unbind() const override { glBindTexture(TYPE, 0); } \
		void update UPDATE override; \
	private: \
		texture_options m_options; \
		void init(const texture_options& options) { glGenTextures(1, &m_id); bind(0); glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, get_min_filter(options.min_filter)); glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, get_mag_filter(options.mag_filter)); glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, get_wrap_s(options.wrap_s)); glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, get_wrap_t(options.wrap_t)); } };

	T(texture2d, GL_TEXTURE_2D, (s_type w, s_type h, const void* const data, const texture_options& options), (s_type x, s_type y, s_type w, s_type h, const void* const data));
	T(texture2d_array, GL_TEXTURE_2D_ARRAY, (s_type w, s_type h, s_type f, const void* const data, const texture_options& options), (s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data));

#undef T
}
