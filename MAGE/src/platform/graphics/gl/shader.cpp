#include "pch.h"
#include "shader.h"

namespace mage::gfx
{
	vertex_shader* vertex_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new mage::gl::vertex_shader(s, p);
	}
	tessellation_control_shader* tessellation_control_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new mage::gl::tessellation_control_shader(s, p);
	}
	tessellation_eval_shader* tessellation_eval_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new mage::gl::tessellation_eval_shader(s, p);
	}
	geometry_shader* geometry_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new mage::gl::geometry_shader(s, p);
	}
	fragment_shader* fragment_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new mage::gl::fragment_shader(s, p);
	}
}



namespace mage::gl
{
	template<GLenum TARGET>
	shader<TARGET>::~shader()
	{
		glDeleteShader(m_id);
	}



	template<GLenum TARGET>
	shader<TARGET>::shader(const std::string& s, const mage::gfx::shader_preprocessor& p) :
		mage::gfx::shader(s, p)
	{
		compile(parse(s, p));
	}



	template<GLenum TARGET>
	int shader<TARGET>::get_status(GLenum status) const
	{
		int result;
		glGetShaderiv(m_id, status, &result);
		return result;
	}
	template<GLenum TARGET>
	std::string shader<TARGET>::parse(const std::string& s, const mage::gfx::shader_preprocessor& p) const
	{
		std::ifstream in(s);
		MAGE_CORE_ASSERT(in.is_open(), "Error opening OpenGL shader file {}", s);

		std::string line;
		std::stringstream src;

		while (getline(in, line))
			src << p(line) << '\n';

		return src.str();
	}
	template<GLenum TARGET>
	void shader<TARGET>::compile(const std::string& src)
	{
		m_id = glCreateShader(TARGET);
		const char* ptr = src.c_str();
		glShaderSource(m_id, 1, &ptr, nullptr);

		glCompileShader(m_id);
		if (!get_status(GL_COMPILE_STATUS))
		{
			MAGE_CORE_ERROR("OpenGL shader compilation failed");
			MAGE_CORE_ERROR("Source:\n{}", src.c_str());

			int length = get_status(GL_INFO_LOG_LENGTH);
			char* buf = new char[length];
			glGetShaderInfoLog(m_id, length, nullptr, buf);
			// remove automatic newline
			buf[length - 2] = 0;
			MAGE_CORE_ERROR("{}", buf);
			delete[] buf;

			glDeleteShader(m_id);
			MAGE_CORE_ASSERT(false, "");
		}
	}
}
