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



/**
 * BASE
 */
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

// for some reason all overrides can't be defined in .cpp
#define B(NAME, TARGET, CREATE, DELETE) \
	template<GLenum USAGE> \
	class NAME : public mage::gl::buffer<mage::gfx::NAME::s_type, TARGET, USAGE>, public mage::gfx::NAME { \
		using mage::gl::buffer<mage::gfx::NAME::s_type, TARGET, USAGE>::m_id; \
	public: \
		MAGE_DM(NAME); \
		~NAME() { MAGE_CORE_TRACE(DELETE, m_id); } \
		void bind() const override { mage::gl::buffer<s_type, TARGET, USAGE>::bind(); } \
		void unbind() const override { mage::gl::buffer<s_type, TARGET, USAGE>::unbind(); } \
		void update(s_type* data, size_t count, size_t offset) const override { mage::gl::buffer<s_type, TARGET, USAGE>::update(data, count, offset); arrcopy(count, data, m_data + offset); } \
		void load(input_file& in) override { mage::gfx::NAME::load(in); mage::gl::buffer<mage::gfx::NAME::s_type, TARGET, USAGE>::write(m_data, m_count); } \
	protected: \
		NAME(s_type* data, size_t count) : mage::gl::buffer<s_type, TARGET, USAGE>(count), mage::gfx::NAME(count) { write(data, count); MAGE_CORE_TRACE(CREATE, m_id); } \
		NAME(const NAME& other, size_t count) : mage::gl::buffer<s_type, TARGET, USAGE>(count), mage::gfx::NAME(other, count) {} \
		NAME(input_file& in) : mage::gl::buffer<s_type, TARGET, USAGE>(0), mage::gfx::NAME(0) { load(in); } \
		void write(s_type* data, size_t count) const override { mage::gl::buffer<mage::gfx::NAME::s_type, TARGET, USAGE>::write(data, count); arrcopy(count, data, m_data); } };

	B(retained_index_buffer, GL_ELEMENT_ARRAY_BUFFER, "Create IB {}", "Delete IB {}");
	B(retained_vertex_buffer, GL_ARRAY_BUFFER, "Create VB {}", "Delete VB {}");

#undef B



/**
 * IMPL
 */
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


/**
 * RETAINED IMPL
 */
#define B(NAME, TARGET) \
	class NAME : public mage::gl::retained_index_buffer<TARGET> { \
	public: \
		NAME(s_type* indices, size_t count) : retained_index_buffer<TARGET>(indices, count) {} \
		NAME(const NAME& other, size_t count) : retained_index_buffer<TARGET>(other, count) {} \
		NAME(input_file& in) : retained_index_buffer<TARGET>(in) {} \
		MAGE_DCM(NAME);	};

	B(retained_static_index_buffer, GL_STATIC_DRAW);
	B(retained_dynamic_index_buffer, GL_DYNAMIC_DRAW);

#undef B

#define B(NAME, TARGET) \
	class NAME : public mage::gl::retained_vertex_buffer<TARGET> { \
	public: \
		NAME(s_type* indices, size_t count) : retained_vertex_buffer<TARGET>(indices, count) {} \
		NAME(const NAME& other, size_t count) : retained_vertex_buffer<TARGET>(other, count) {} \
		NAME(input_file& in) : retained_vertex_buffer<TARGET>(in) {} \
		MAGE_DCM(NAME);	};

	B(retained_static_vertex_buffer, GL_STATIC_DRAW);
	B(retained_dynamic_vertex_buffer, GL_DYNAMIC_DRAW);

#undef B
}
