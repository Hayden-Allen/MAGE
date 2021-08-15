#pragma once
#include "pch.h"
#include "mage/graphics/retained_buffer.h"
#include "buffer.h"

namespace mage::gl
{
	template<GLenum TARGET, GLenum USAGE, typename T>
	class retained_buffer : public T
	{
	public:
		MAGE_DM(retained_buffer);
		virtual ~retained_buffer()
		{
			glDeleteBuffers(1, &this->m_id);
		}
		
		
		void bind() const override
		{
			glBindBuffer(TARGET, this->m_id);
		}
		void unbind() const override
		{
			glBindBuffer(TARGET, 0);
		}
		void update(T::s_type* data, size_t count, size_t offset) const override
		{
			bind();
			glBufferSubData(TARGET, offset, count * sizeof(T::s_type), data);
			unbind();
			arrcopy(count, data, this->m_data + offset);
		}
		void save(output_file& out) const override
		{
			T::save(out);
		}
		void load(input_file& in) override
		{
			T::load(in);
			write(this->m_data, this->m_count);
		}
	protected:
		retained_buffer(T::s_type* data, size_t count) :
			T(count)
		{
			glGenBuffers(1, &this->m_id);
			write(data, count);
		}
		retained_buffer(const retained_buffer& other, size_t count) :
			T(other, count)
		{
			glGenBuffers(1, &this->m_id);
		}
		retained_buffer(input_file& in) :
			T(0)
		{
			glGenBuffers(1, &this->m_id);
			load(in);
		}


		void write(T::s_type* data, size_t count) const override
		{
			bind();
			glBufferData(TARGET, count * sizeof(T::s_type), data, USAGE);
			unbind();
			arrcopy(count, data, this->m_data);
		}
	};
}
