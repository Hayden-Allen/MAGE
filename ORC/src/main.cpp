#include <mage.h>

namespace orc
{
	class orc_application : public mage::application
	{
	public:
		orc_application()
		{

		}
		MAGE_DCM(orc_application);
		~orc_application()
		{

		}


		void run() const override
		{
			mage::key_press_event e(65, true);
			MAGE_TRACE(e.to_string());

			while (true);
		}
	};
}


mage::application* mage::create_application()
{
	return new orc::orc_application();
}
