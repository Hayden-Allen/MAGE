#include "pch.h"
#include "imgui.h"

namespace orc
{
	class orc_layer : public mage::layer
	{
	public:
		orc_layer() :
			mage::layer("ORC")
		{
			MAGE_ERROR("CREATE ORC LAYER");
		}
		MAGE_DCM(orc_layer);
		~orc_layer()
		{
			MAGE_ERROR("DELETE ORC LAYER");
		}
	};

	

	class orc_imgui_layer : public mage::imgui_layer
	{
	public:
		orc_imgui_layer() :
			mage::imgui_layer("ORC ImGui")
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

			ImGui::Begin("Test");
			ImGui::Text("Hello, world!");
			ImGui::End();

			return false;
		}
	};



	class orc_application : public mage::application
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
