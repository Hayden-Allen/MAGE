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



	template<GLenum INTERNAL, GLenum FORMAT, GLenum TYPE>
	class framebuffer_attachment :
		public mage::gfx::framebuffer_attachment,
		public texture2d
	{
	public:
		MAGE_DCM(framebuffer_attachment);
		virtual ~framebuffer_attachment();
	protected:
		framebuffer_attachment(s_type w, s_type h);


		void update() const override
		{
			texture2d::bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL, m_w, m_h, 0, FORMAT, TYPE, nullptr);
		}
	};



#define F(NAME, INTERNAL, FORMAT, TYPE) \
	class NAME final : public framebuffer_attachment<INTERNAL, FORMAT, TYPE>, public mage::gfx::NAME { \
		using texture2d::m_id; \
	public: \
		NAME(s_type w, s_type h); \
		MAGE_DCM(NAME); \
		~NAME() {} \
		mage::gfx::renderer_id_t get_id() const override { return texture2d::get_id(); } \
		void bind(uint32_t slot) const override { texture2d::bind(slot); } \
		void unbind() const override { texture2d::unbind(); } \
		mage::gfx::framebuffer_attachment_type get_type() const override { return mage::gfx::NAME::get_type(); } \
	protected: \
		void bind() const override { mage::gfx::texture::bind(); } \
		void update() const override { mage::gl::framebuffer_attachment<INTERNAL, FORMAT, TYPE>::update(); } };
	
	F(framebuffer_color_attachment, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	F(framebuffer_depth_attachment, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);

#undef F
}
