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
		texture2d(s_type w, s_type h) :
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


		static retained_texture2d* create(s_type w, s_type h, size_t count, const texture_options& options);
		static retained_texture2d* create(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options);
		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override
		{
			MAGE_CORE_ASSERT(x < m_w&& y < m_h, "Invalid retained_texture2d update lower bound <{}, {}> (must be < <{}, {}>)", x, y, m_w, m_h);
			MAGE_CORE_ASSERT(x + w < m_w&& y + h < m_h, "Invalid retained_texture2d update upper bound <{}, {}> (must be < <{}, {}>)", x, y, m_w, m_h);

			const uint32_t* const idata = MAGE_CAST(const uint32_t* const, data);
			for (size_t i = 0; i < h; i++)
				for (size_t j = 0; j < w; j++)
					m_data[(y + i) * m_w + (x + j)] = idata[i * w + j];
		}
		void save(output_file& out) const override
		{
			out.uint(m_w).uint(m_h);
			out.ulong(m_count);
			out.write(m_data, m_count);
		}
		void load(input_file& in) override
		{
			m_w = in.uint();
			m_h = in.uint();
			m_count = in.ulong();
			m_data = new uint32_t[m_count];
			in.read(m_data, m_count);
		}
	protected:
		size_t m_count;
		uint32_t* m_data;


		// don't allocate space (used when loading from a file)
		retained_texture2d(s_type w, s_type h, size_t count) :
			texture2d(w, h),
			m_count(count),
			m_data(nullptr)
		{}
		// allocate space, fill with 0's if nullptr given
		retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data) :
			texture2d(w, h),
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
