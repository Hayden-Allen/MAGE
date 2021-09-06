#include "pch.h"
#include "layer.h"

namespace magl
{
	class application final : public coga::application
	{
	public:
		application(const coga::window_constructor& c) :
			coga::application(c)
		{
			COGA_ERROR("CREATE MAGL APP");
			attach_layer(new layer());
		}
		COGA_DCM(application);
		~application()
		{
			COGA_ERROR("DELETE MAGL APP");
		}
	};
}


coga::application* coga::create_application()
{
	return new magl::application(coga::window_constructor("Test", 1280, 720, false, { 0.f, 0.f, 1.f, 1.f }));
}
