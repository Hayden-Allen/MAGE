#include "pch.h"
#include "renderer.h"

namespace mage::gfx
{
	renderer* renderer::create()
	{
		return new mage::gl::renderer();
	}
}



namespace mage::gl
{
	void renderer::set_clear_color(const color<float>& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void renderer::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void renderer::draw(const mage::gfx::index_buffer* const indices, const mage::gfx::vertex_array* const vertices) const
	{
		indices->bind();
		vertices->bind();
		glDrawElements(GL_TRIANGLES, indices->get_count<GLsizei>(), mage::gfx::get_shader_type<mage::gfx::index_buffer::s_type>(), nullptr);
	}
	void renderer::draw(const mage::gfx::shader_program* const shader, const mage::gfx::index_buffer* const indices, const mage::gfx::vertex_array* const vertices) const
	{
		shader->bind();
		draw(indices, vertices);
	}
	void renderer::render(const window* const window) const
	{
		glfwPollEvents();
		glfwSwapBuffers(MAGE_CAST(GLFWwindow*, window->get_native_window()));
	}
}
