#pragma once
#include "pch.h"
#include "texture_options.h"
#include "mage/graphics/texture.h"

namespace mage::gl
{
	template<typename T, GLenum TARGET, typename ... ARGS>
	class texture : public T
	{
	public:
		MAGE_DCM(texture);
		virtual ~texture()
		{
			glDeleteTextures(1, &this->m_id);
		}
		
		
		void bind(uint32_t slot) const
		{
			MAGE_CORE_ASSERT(slot < 32, "Invalid OpenGL texture slot");
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(TARGET, this->m_id);
		}
		void unbind() const override
		{
			glBindTexture(TARGET, 0);
		}
	protected:
		texture_options m_options;


		texture(const texture_options& options, T::s_type w, T::s_type h, const ARGS& ... args) :
			T(w, h, args...),
			m_options(options)
		{
			init(options);
		}


		void init(const texture_options& options);
	};



	class texture2d : public mage::gl::texture<mage::gfx::texture2d, GL_TEXTURE_2D>
	{
	public:
		texture2d(s_type w, s_type h, const void* const data, const texture_options& options);
		MAGE_DCM(texture2d);


		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override;
	};



	class retained_texture2d : public mage::gl::texture<mage::gfx::retained_texture2d, GL_TEXTURE_2D, size_t, const uint32_t* const>
	{
	public:
		retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options);
		retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options);
		MAGE_DCM(retained_texture2d);


		void load(input_file& in) override;
		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override;
		void save(output_file& out) const override
		{
			mage::gfx::retained_texture2d::save(out);
			serialize_texture_options(m_options, out);
		}
		void save(output_file& out, s_type x, s_type y, s_type w, s_type h) const override
		{
			mage::gfx::retained_texture2d::save(out, x, y, w, h);
			serialize_texture_options(m_options, out);
		}
	};



	class texture2d_array : public mage::gl::texture<mage::gfx::texture2d_array, GL_TEXTURE_2D_ARRAY, mage::gfx::texture2d_array::s_type>
	{
	public:
		texture2d_array(s_type w, s_type h, s_type f, const void* const data, const texture_options& options);
		MAGE_DCM(texture2d_array);


		
		void update(s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data) override;
	};
}
