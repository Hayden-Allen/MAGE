#include "pch.h"
#include "imgui.h"

namespace orc
{
	class orc_layer final : public mage::layer
	{
	public:
		orc_layer() :
			mage::layer("ORC"),
			m_vertex_array(nullptr),
			m_vertex_buffer(nullptr),
			m_index_buffer(nullptr)
		{
			MAGE_ERROR("CREATE ORC LAYER");
			uint32_t indices[3] = { 0, 1, 2 };
			m_index_buffer = mage::gfx::index_buffer::create_static(indices, mage::arrlen(indices));
			float vertices[6] =
			{
				-.5f, -.5f,
				 .5f, -.5f,
				 0.f,  .5f
			};
			m_vertex_buffer = mage::gfx::vertex_buffer::create_static(vertices, mage::arrlen(vertices));
			m_vertex_array = mage::gfx::vertex_array::create_static(m_vertex_buffer, mage::gl::vertex_array_description({ 2 }));
		}
		MAGE_DCM(orc_layer);
		~orc_layer()
		{
			MAGE_ERROR("DELETE ORC LAYER");
			delete m_vertex_array;
			delete m_vertex_buffer;
			delete m_index_buffer;
		}


		bool on_app_draw(mage::app_draw_event& e) override
		{
			m_vertex_array->bind();
			m_index_buffer->bind();
			glDrawElements(GL_TRIANGLES, MAGE_CAST(GLsizei, m_index_buffer->get_count()), mage::gl::get_type_enum<mage::gfx::index_buffer::s_type>(), nullptr);
			return false;
		}
	private:
		mage::gfx::vertex_array* m_vertex_array;
		mage::gfx::vertex_buffer* m_vertex_buffer;
		mage::gfx::index_buffer* m_index_buffer;
	};

	

	class orc_imgui_layer final : public mage::windows_imgui_layer
	{
	public:
		orc_imgui_layer() :
			mage::windows_imgui_layer("ORC ImGui")
		{
			MAGE_ERROR("CREATE ORC IMGUI LAYER");
		}
		MAGE_DCM(orc_imgui_layer);
		~orc_imgui_layer()
		{
			MAGE_ERROR("DELETE ORC IMGUI LAYER");
		}


		bool on_app_draw(mage::app_draw_event& e) override
		{
			static bool show = true;
			ImGui::ShowDemoWindow(&show);

			return false;
		}
	};



	class orc_application final : public mage::application
	{
	public:
		orc_application(const mage::window_constructor& c) :
			application(c)
		{
			MAGE_ERROR("CREATE ORC APP");
			attach_layer(new orc_layer());
			attach_layer_top(new orc_imgui_layer());
		}
		MAGE_DCM(orc_application);
		~orc_application()
		{
			MAGE_ERROR("DELETE ORC APP");
		}
	};
}


mage::application* mage::create_application()
{
	return new orc::orc_application(mage::window_constructor("Test", 1280, 720, false, { 0.f, 0.f, 1.f, 1.f }));
}
