#include "pch.h"
#include "orc/layer/layer.h"
#include "orc/layer/imgui_layer.h"

namespace orc
{
	class application final : public coga::application
	{
	public:
		application(const coga::window_constructor& c) :
			coga::application(c)
		{
			COGA_ERROR("CREATE ORC APP");
			auto l = new layer();
			attach_layer(l);
			attach_layer_top(new imgui_layer(l));
		}
		COGA_DCM(application);
		~application()
		{
			COGA_ERROR("DELETE ORC APP");
		}
	};
}


coga::application* coga::create_application()
{
	return new orc::application(coga::window_constructor("Test", 1280, 720, false, { 0.f, 0.f, 1.f, 1.f }));
}
