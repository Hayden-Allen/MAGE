#include "pch.h"
#include "layer/layer.h"
#include "layer/imgui_layer.h"

namespace orc
{
	class orc_application final : public mage::application
	{
	public:
		orc_application(const mage::window_constructor& c) :
			application(c)
		{
			MAGE_ERROR("CREATE ORC APP");
			auto l = new layer();
			attach_layer(l);
			attach_layer_top(new imgui_layer(l));
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
