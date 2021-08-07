#pragma once
#include "pch.h"
#include "mage/graphics/shader.h"

namespace mage::gl
{
	template<GLenum TARGET>
	class shader : public mage::gfx::shader
	{
	public:
		MAGE_DCM(shader);
		~shader();


		void bind() const override
		{
			MAGE_CORE_ASSERT(false, "OpenGL shaders cannot be bound");
		}
		void unbind() const override
		{
			MAGE_CORE_ASSERT(false, "OpenGL shaders cannot be unbound");
		}
	protected:
		shader(const std::string& s, const mage::gfx::shader_preprocessor& p = mage::gfx::shader_preprocessor());


		int get_status(GLenum status) const;
		std::string parse(const std::string& s, const mage::gfx::shader_preprocessor& p) const;
		void compile(const std::string& src);
	};



#define S(TARGET, CLASS, PRIORITY, NAME) \
	class CLASS final : public shader<TARGET>, public mage::gfx::CLASS { \
		using shader<TARGET>::m_id; \
	public:\
		CLASS(const std::string& src, const mage::gfx::shader_preprocessor& p = mage::gfx::shader_preprocessor()) : shader<TARGET>(src, p), mage::gfx::CLASS(src, p) {} \
		MAGE_DCM(CLASS); \
		void bind() const override { shader<TARGET>::bind(); } \
		void unbind() const override { shader<TARGET>::unbind(); } \
		mage::gfx::renderer_id_t get_id() const override { return shader<TARGET>::m_id; } \
		MAGE_SHADER_PRIORITY(PRIORITY); };

	S(GL_VERTEX_SHADER, vertex_shader, 0, vertex);
	S(GL_TESS_CONTROL_SHADER, tessellation_control_shader, 1, tessellation control);
	S(GL_TESS_EVALUATION_SHADER, tessellation_eval_shader, 2, tessellation evaluation);
	S(GL_GEOMETRY_SHADER, geometry_shader, 3, geometry);
	S(GL_FRAGMENT_SHADER, fragment_shader, 4, fragment);

#undef S
}
