#pragma once
#include "pch.h"
#include "mage/graphics/buffer.h"

namespace mage::gl
{
	template<GLenum TARGET, GLenum USAGE, typename T>
	class buffer : public T
	{
	protected:
		using s_type = T::s_type;
	public:
		MAGE_DM(buffer);
		virtual ~buffer()
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
		}
	protected:
		buffer(size_t count) :
			T(count)
		{
			glGenBuffers(1, &this->m_id);
		}


		void write(T::s_type* data, size_t count) const override
		{
			bind();
			glBufferData(TARGET, count * sizeof(T::s_type), data, USAGE);
			unbind();
		}
	};
}
