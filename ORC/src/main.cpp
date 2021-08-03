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
			while (true);
		}
	};
}


mage::application* mage::create_application()
{
	return new orc::orc_application();
}
