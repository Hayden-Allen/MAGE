#include "pch.h"
#include "imgui.h"

namespace orc
{
	class orc_layer final : public mage::layer
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



	class orc_imgui_layer2 final : public mage::windows_imgui_layer
	{
	public:
		orc_imgui_layer2() :
			mage::windows_imgui_layer("ORC ImGui 2")
		{
			MAGE_ERROR("CREATE ORC IMGUI LAYER 2");
		}
		MAGE_DCM(orc_imgui_layer2);
		~orc_imgui_layer2()
		{
			MAGE_ERROR("DELETE ORC IMGUI LAYER 2");
		}


		bool on_app_draw(mage::app_draw_event& e) override
		{
			ImGui::Begin("Test");
			ImGui::Text("%.2fms | %.2ffps", e.get_delta_time(), 1000.f / e.get_delta_time());
			ImGui::End();

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
			attach_layer_top(new orc_imgui_layer2());
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
