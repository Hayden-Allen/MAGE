#include <mage.h>

namespace orc
{
	class orc_application : public mage::application
	{
	public:
		orc_application(const mage::window_constructor& c) :
			application(c)
		{}
		MAGE_DCM(orc_application);


		void run() const override
		{
			while (m_running)
				m_window->on_update();
		}
	protected:
		void on_event(mage::event& e) override
		{
			MAGE_TRACE("{}", e.to_string());
			mage::application::on_event(e);
		}
	};
}


mage::application* mage::create_application()
{
	return new orc::orc_application(mage::window_constructor("Test", 800, 600, false, { 0.f, 0.f, 1.f, 1.f }));
}
