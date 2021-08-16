#include "pch.h"
#include "shader_type.h"
#include "mage/graphics/renderer.h"

namespace mage::gfx
{
	void renderer::set_clear_color(const color<float>& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void renderer::draw(const mage::gfx::index_buffer* const indices, const mage::gfx::vertex_array* const vertices)
	{
		// MAKE SURE TO BIND IN THIS ORDER. I don't know why, but binding the index buffer first causes problems sometimes. It probably has to do with the fact that, in this implementation, vertex arrays aren't "associated" with an index buffer by default, unless one is bound before the vertex array is contructed.
		// I prefer vertex arrays and index buffers to be separate by default, essentially using the vertex array as a wrapper for a vertex buffer that includes its description. I'm not sure if my implementation actually achieves this separation, but binding in this order allows me to ACT like they are separate even if they aren't.
		vertices->bind();
		indices->bind();
		glDrawElements(GL_TRIANGLES, indices->get_count<GLsizei>(), mage::gfx::get_shader_type<mage::gfx::index_buffer::s_type>(), nullptr);
		indices->unbind();
		vertices->unbind();
	}
	void renderer::draw(const mage::gfx::shader_program* const shader, const mage::gfx::index_buffer* const indices, const mage::gfx::vertex_array* const vertices)
	{
		shader->bind();
		draw(indices, vertices);
		shader->unbind();
	}
	void renderer::render(const window* const window)
	{
		glfwPollEvents();
		glfwSwapBuffers(MAGE_CAST(GLFWwindow*, window->get_native_window()));
	}
}
