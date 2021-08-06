#pragma once
#include "pch.h"
#include "mage/graphics/buffer.h"

namespace mage::gl
{
	template<typename T, GLenum TARGET, GLenum USAGE>
	class buffer : public mage::gfx::buffer<T>
	{
	public:
		MAGE_DCM(buffer);
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
		void update(T* data, size_t count, size_t offset) const override
		{
			bind();
			glBufferSubData(TARGET, offset, count * sizeof(T), data);
		}
	protected:
		buffer(size_t count) :
			mage::gfx::buffer<T>(count)
		{
			glGenBuffers(1, &this->m_id);
		}


		void write(T* data, size_t count) const override
		{
			bind();
			glBufferData(TARGET, count * sizeof(T), data, USAGE);
		}
	};

}
