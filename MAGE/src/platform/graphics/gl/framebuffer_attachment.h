#pragma once
#include "pch.h"
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



	template<GLenum INTERNAL, GLenum FORMAT, GLenum TYPE>
	class framebuffer_attachment : public mage::gfx::framebuffer_attachment
	{
	public:
		MAGE_DCM(framebuffer_attachment);
		virtual ~framebuffer_attachment();


		void bind() const override
		{
			glBindTexture(GL_TEXTURE_2D, m_id);
		}
		void unbind() const override
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		void update() const override
		{
			bind();
			glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL, m_w, m_h, 0, FORMAT, TYPE, nullptr);
		}
	protected:
		framebuffer_attachment(s_type w, s_type h);
	};

#define F(NAME, INTERNAL, FORMAT, TYPE) \
	class NAME final : public framebuffer_attachment<INTERNAL, FORMAT, TYPE>, public mage::gfx::NAME { \
		using mage::gl::framebuffer_attachment<INTERNAL, FORMAT, TYPE>::m_id; \
	public: \
		NAME(s_type w, s_type h); \
		MAGE_DCM(NAME); \
		~NAME() {} \
		mage::gfx::renderer_id_t get_id() const override { return mage::gl::framebuffer_attachment<INTERNAL, FORMAT, TYPE>::get_id(); } \
		void bind() const override { mage::gl::framebuffer_attachment<INTERNAL, FORMAT, TYPE>::bind(); } \
		void unbind() const override { mage::gl::framebuffer_attachment<INTERNAL, FORMAT, TYPE>::unbind(); } \
		void update() const override { mage::gl::framebuffer_attachment<INTERNAL, FORMAT, TYPE>::update(); } \
		mage::gfx::framebuffer_attachment_type get_type() const override { return mage::gfx::NAME::get_type(); } };
	
	F(framebuffer_color_attachment, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	F(framebuffer_depth_attachment, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);

#undef F
}
