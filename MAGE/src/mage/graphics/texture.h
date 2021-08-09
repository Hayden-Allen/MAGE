#pragma once
#include "pch.h"
#include "render_object.h"
#include "mage/util/dimensional.h"

namespace mage::gfx
{
	class texture :
		public virtual render_object,
		public virtual dimensional<uint32_t>
	{
	public:
		MAGE_DCM(texture);
		virtual ~texture() {}


		virtual void bind(uint32_t slot) const = 0;
	protected:
		texture(s_type w, s_type h, void* data) :
			dimensional<s_type>(w, h)
		{}


		void bind() const override
		{
			bind(0);
		}
	};



	class texture2d : public texture
	{
	public:
		MAGE_DCM(texture2d);
		virtual ~texture2d() {}


		static texture2d* create(s_type w, s_type h, void* data);
	protected:
		texture2d(s_type w, s_type h, void* data) :
			texture(w, h, data)
		{}
	};



	class texture2d_array : public texture
	{
	public:
		MAGE_DCM(texture2d_array);
		virtual ~texture2d_array() {}


		static texture2d_array* create(s_type w, s_type h, s_type f, void* data);
		s_type get_frame_count() const
		{
			return m_frames;
		}
	protected:
		s_type m_frames;


		texture2d_array(s_type w, s_type h, s_type f, void* data) :
			texture(w, h, data),
			m_frames(f)
		{}
	};
}
