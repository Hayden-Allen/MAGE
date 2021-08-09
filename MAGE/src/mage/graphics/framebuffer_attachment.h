#pragma once
#include "pch.h"
#include "render_object.h"
#include "mage/util/dimensional.h"

namespace mage::gfx
{
	enum class framebuffer_attachment_type
	{
		none = 0,
		color, depth
	};




	class framebuffer_attachment :
		public virtual render_object,
		public virtual dimensional<uint32_t>
	{
		friend class framebuffer;
	public:
		MAGE_DCM(framebuffer_attachment);
		virtual ~framebuffer_attachment() {}


		virtual void bind(uint32_t) const = 0;
		virtual framebuffer_attachment_type get_type() const = 0;
		virtual void update() const = 0;
	protected:
		framebuffer_attachment(s_type w, s_type h) :
			dimensional<uint32_t>(w, h)
		{}
	};



#define F(NAME, TYPE) \
	class NAME : public framebuffer_attachment { \
	public: \
		MAGE_DCM(NAME); \
		virtual ~NAME() {} \
		static NAME* create(s_type w, s_type h); \
		framebuffer_attachment_type get_type() const override { return framebuffer_attachment_type::TYPE; } \
	protected: \
		NAME(s_type w, s_type h) : framebuffer_attachment(w, h) {} };

	F(framebuffer_color_attachment, color);
	F(framebuffer_depth_attachment, depth);

#undef F
}
