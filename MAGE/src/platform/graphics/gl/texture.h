#pragma once
#include "pch.h"
#include "texture_options.h"
#include "mage/graphics/texture.h"

namespace mage::gl
{
#define T(NAME, TYPE, SIG, UPDATE, ...) \
	class NAME : public mage::gfx::NAME { \
	public: \
		NAME SIG; \
		__VA_ARGS__ \
		MAGE_DCM(NAME); \
		~NAME() { glDeleteTextures(1, &m_id); } \
		void bind(uint32_t slot) const { MAGE_CORE_ASSERT(slot < 32, "Invalid OpenGL texture slot"); glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(TYPE, m_id); } \
		void unbind() const override { glBindTexture(TYPE, 0); } \
		void update UPDATE override; \
	protected: \
		texture_options m_options; \
		void init(const texture_options& options) { glGenTextures(1, &m_id); bind(0); glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, get_min_filter(options.min_filter)); glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, get_mag_filter(options.mag_filter)); glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, get_wrap_s(options.wrap_s)); glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, get_wrap_t(options.wrap_t)); } };

	T(texture2d, GL_TEXTURE_2D, (s_type w, s_type h, const void* const data, const texture_options& options), (s_type x, s_type y, s_type w, s_type h, const void* const data));
	T(texture2d_array, GL_TEXTURE_2D_ARRAY, (s_type w, s_type h, s_type f, const void* const data, const texture_options& options), (s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data));

#undef T


	class retained_texture2d : public mage::gfx::retained_texture2d
	{
	public:
		retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options);
		retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options);
		MAGE_DCM(retained_texture2d);
		~retained_texture2d()
		{
			glDeleteTextures(1, &m_id);
		}


		void save(output_file& out) const override;
		void load(input_file& in) override;
		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override;
		void bind(uint32_t slot) const
		{
			MAGE_CORE_ASSERT(slot < 32, "Invalid OpenGL texture slot");
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_id);
		} 
		void unbind() const override
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	protected:
		texture_options m_options;
		void init(const texture_options& options)
		{
			glGenTextures(1, &m_id);
			bind(0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, get_min_filter(options.min_filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, get_mag_filter(options.mag_filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, get_wrap_s(options.wrap_s));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, get_wrap_t(options.wrap_t));
		}
	};
}
