#pragma once
#include "pch.h"
#include "texture.h"
#include "mage/graphics/framebuffer_attachment.h"
#include "mage/util/dimensional.h"

namespace mage::gl
{
	static GLenum framebuffer_attachment_enum[] =
	{
		GL_NONE, GL_COLOR_ATTACHMENT0, GL_DEPTH_STENCIL_ATTACHMENT
	};
	static GLenum get_framebuffer_attachment_enum(mage::gfx::framebuffer_attachment_type type)
	{
		MAGE_CORE_ASSERT(type != mage::gfx::framebuffer_attachment_type::none, "Invalid OpenGL framebuffer attachment type");
		return framebuffer_attachment_enum[MAGE_CAST(size_t, type)];
	}



	template<typename T, typename ... ARGS>
	class framebuffer_attachment : public T
	{
	protected:
		using s_type = T::s_type;
	public:
		MAGE_DCM(framebuffer_attachment);
		virtual ~framebuffer_attachment() {}
	protected:
		framebuffer_attachment(s_type w, s_type h, const ARGS& ... args) :
			T(w, h, args...),
			dimensional<s_type>(w, h)
		{}
	};



	class framebuffer_color_attachment final : public mage::gl::framebuffer_attachment<mage::gfx::framebuffer_color_attachment<mage::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>
	{
	public:
		framebuffer_color_attachment(s_type w, s_type h);
		MAGE_DCM(framebuffer_color_attachment);
	protected:
		void reset() const override
		{
			bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_w, this->m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			unbind();
		}
	};



	class framebuffer_depth_attachment final : public mage::gl::framebuffer_attachment<mage::gfx::framebuffer_depth_attachment<mage::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>
	{
	public:
		framebuffer_depth_attachment(s_type w, s_type h);
		MAGE_DCM(framebuffer_depth_attachment);
	protected:
		void reset() const override
		{
			bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->m_w, this->m_h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
			unbind();
		}
	};

	/*class framebuffer_color_attachment final :
		public texture2d,
		public mage::gfx::framebuffer_color_attachment
	{
	public:
		framebuffer_color_attachment(s_type w, s_type h);
		MAGE_DCM(framebuffer_color_attachment);
	};



	class framebuffer_depth_attachment final :
		public texture2d,
		public mage::gfx::framebuffer_depth_attachment
	{
	public:
		framebuffer_depth_attachment(s_type w, s_type h);
		MAGE_DCM(framebuffer_depth_attachment);


		mage::gfx::renderer_id_t get_id() const override
		{
			return mage::gl::texture2d::get_id();
		}
		void bind(uint32_t slot) const override
		{
			mage::gl::texture2d::bind(slot);
		}
		void unbind() const override
		{
			mage::gl::texture2d::unbind();
		}
		mage::gfx::framebuffer_attachment_type get_type() const override
		{
			return mage::gfx::framebuffer_depth_attachment::get_type();
		}
	protected:
		void reset() const override
		{
			bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_w, m_h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
			unbind();
		}
	private:
		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override
		{
			mage::gl::texture2d::update(x, y, w, h, data);
		}
	};*/
}
