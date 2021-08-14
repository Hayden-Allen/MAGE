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
			unbind();
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
			unbind();
		}
	};



#define B(NAME, TARGET, STRING) \
	template<GLenum USAGE> \
	class NAME : public mage::gl::buffer<mage::gfx::NAME::s_type, TARGET, USAGE>, public mage::gfx::NAME { \
		using mage::gl::buffer<mage::gfx::NAME::s_type, TARGET, USAGE>::m_id; \
	public: \
		MAGE_DCM(NAME); \
		~NAME() { MAGE_CORE_TRACE(STRING, m_id); } \
		void bind() const override; \
		void unbind() const override; \
		void update(s_type* data, size_t count, size_t offset) const override; \
	protected: \
		NAME(s_type* vertices, size_t count); \
		void write(s_type* data, size_t count) const override; };

	B(index_buffer, GL_ELEMENT_ARRAY_BUFFER, "Delete IB {}");
	B(vertex_buffer, GL_ARRAY_BUFFER, "Delete VB {}");

#undef B



#define B(NAME, TARGET) \
	class NAME : public mage::gl::index_buffer<TARGET> { \
	public: \
		NAME(s_type* indices, size_t count) : index_buffer<TARGET>(indices, count) {} \
		MAGE_DCM(NAME);	};

	B(static_index_buffer, GL_STATIC_DRAW);
	B(dynamic_index_buffer, GL_DYNAMIC_DRAW);

#undef B



#define B(NAME, TARGET) \
	class NAME : public mage::gl::vertex_buffer<TARGET> { \
	public: \
		NAME(s_type* indices, size_t count) : vertex_buffer<TARGET>(indices, count) {} \
		MAGE_DCM(NAME);	};

	B(static_vertex_buffer, GL_STATIC_DRAW);
	B(dynamic_vertex_buffer, GL_DYNAMIC_DRAW);

#undef B
}
