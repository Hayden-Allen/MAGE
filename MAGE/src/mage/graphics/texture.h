#pragma once
#include "pch.h"
#include "render_object.h"
#include "texture_options.h"
#include "mage/io/serializable.h"
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



	class retained_texture2d :
		public texture2d,
		public serializable
	{
	public:
		MAGE_DCM(retained_texture2d);
		virtual ~retained_texture2d()
		{
			delete m_data;
		}


		static retained_texture2d* create(s_type w, s_type h, const uint32_t* const data, size_t count, const texture_options& options);
		void save(output_file& out) const override
		{
			out.ulong(m_count);
			for (size_t i = 0; i < m_count; i++)
				out.uint(m_data[i]);
		}
		void load(input_file& in) override
		{

		}
	protected:
		size_t m_count;
		uint32_t* m_data;


		retained_texture2d(s_type w, s_type h, const uint32_t* const data, size_t count) :
			texture2d(w, h, data),
			m_count(count),
			m_data(new uint32_t[count])
		{
			for (size_t i = 0; i < count; i++)
				m_data[i] = (data ? data[i] : 0);
		}
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
