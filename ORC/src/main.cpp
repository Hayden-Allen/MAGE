#include <mage.h>

namespace orc
{
	class orc_application : public mage::application
	{
	public:
		orc_application() :
			application(mage::window_data("Test", 800, 600, false, { 0.f, 0.f, 1.f, 1.f }))
		{}
		MAGE_DCM(orc_application);


		void run() const override
		{
			while (m_running)
				m_window->on_update();
		}
	};
}


mage::application* mage::create_application()
{
	return new orc::orc_application();
}
