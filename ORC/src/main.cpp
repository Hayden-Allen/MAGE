#include <mage.h>

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


		bool on_app_tick(mage::app_tick_event& e) override
		{
			float x = mage::input::get()->get_mouse_x(), y = mage::input::get()->get_mouse_y();
			MAGE_WARN("<{}, {}>", x, y);
			return true;
		}
	};



	class orc_application : public mage::application
	{
	public:
		orc_application(const mage::window_constructor& c) :
			application(c)
		{
			attach_layer(new orc_layer());
			attach_layer(new mage::imgui_layer());
		}
		MAGE_DCM(orc_application);
	protected:
		void on_event(mage::event& e) override
		{
			mage::application::on_event(e);
			MAGE_TRACE("{}", e.to_string());
		}
	};
}


mage::application* mage::create_application()
{
	return new orc::orc_application(mage::window_constructor("Test", 1280, 720, false, { 0.f, 0.f, 1.f, 1.f }));
}
