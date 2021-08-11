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



#define F(NAME, INTERNAL, FORMAT, TYPE) \
	class NAME final : public texture2d, public mage::gfx::NAME { \
	public: \
		NAME(s_type w, s_type h); \
		MAGE_DCM(NAME); \
		mage::gfx::renderer_id_t get_id() const override { return mage::gl::texture2d::get_id(); } \
		void bind(uint32_t slot) const override { mage::gl::texture2d::bind(slot); } \
		void unbind() const override { mage::gl::texture2d::unbind(); } \
		mage::gfx::framebuffer_attachment_type get_type() const override { return mage::gfx::NAME::get_type(); } \
	protected: \
		void reset() const override { mage::gl::texture2d::bind(0); glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL, m_w, m_h, 0, FORMAT, TYPE, nullptr); } \
	private: \
		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override { mage::gl::texture2d::update(x, y, w, h, data); } };
	
	F(framebuffer_color_attachment, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	F(framebuffer_depth_attachment, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);

#undef F
}
