#pragma once
#include "pch.h"
#include "texture.h"

namespace mage::gfx
{
	enum class framebuffer_attachment_type
	{
		none = 0,
		color, depth
	};




	class framebuffer_attachment : public texture2d
	{
		friend class framebuffer;
	public:
		MAGE_DCM(framebuffer_attachment);
		virtual ~framebuffer_attachment() {}


		virtual framebuffer_attachment_type get_type() const = 0;
		virtual void reset() const = 0;
	protected:
		framebuffer_attachment(s_type w, s_type h) :
			texture2d(w, h, nullptr)
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
