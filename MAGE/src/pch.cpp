#include "pch.h"

#include "mage/application.h"
#include "mage/core.h"
#include "mage/log.h"
#include "mage/window.h"

#include "mage/layer/imgui_layer.h"
#include "mage/layer/layer.h"
#include "mage/layer/layer_stack.h"

#include "mage/util/color.h"
#include "mage/util/dimensional.h"
#include "mage/util/functions.h"
#include "mage/util/positional.h"
#include "mage/util/typed.h"

#include "mage/event/app_event.h"
#include "mage/event/event.h"
#include "mage/event/event_handler.h"
#include "mage/event/event_propagator.h"
#include "mage/event/key_event.h"
#include "mage/event/mouse_event.h"
#include "mage/event/window_event.h"



#ifdef MAGE_PLATFORM_WINDOWS
	#include "platform/windows/windows_window.h"
#endif
