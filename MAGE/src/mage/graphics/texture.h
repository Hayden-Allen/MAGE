#pragma once
#include "pch.h"
#include "render_object.h"
#include "texture_options.h"
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
		texture(s_type w, s_type h) :
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


		static texture2d* create(s_type w, s_type h, const void* const data, const texture_options& options);
		virtual void update(s_type x, s_type y, s_type w, s_type h, const void* const data) = 0;
	protected:
		texture2d(s_type w, s_type h, const void* const data) :
			texture(w, h)
		{}
	};



	class texture2d_array : public texture
	{
	public:
		MAGE_DCM(texture2d_array);
		virtual ~texture2d_array() {}


		static texture2d_array* create(s_type w, s_type h, s_type f, const void* const data, const texture_options& options);
		virtual void update(s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data) = 0;
		s_type get_frame_count() const
		{
			return m_frames;
		}
	protected:
		s_type m_frames;


		texture2d_array(s_type w, s_type h, s_type f, const void* const data) :
			texture(w, h),
			m_frames(f)
		{}
	};
}
