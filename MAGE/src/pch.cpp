#include "pch.h"

#include "mage/application.h"
#include "mage/core.h"
#include "mage/log.h"
#include "mage/window.h"

#include "mage/event/app_event.h"
#include "mage/event/event.h"
#include "mage/event/event_handler.h"
#include "mage/event/event_propagator.h"
#include "mage/event/key_event.h"
#include "mage/event/mouse_event.h"
#include "mage/event/window_event.h"

#include "mage/imgui/imgui_layer.h"

#include "mage/input/input.h"
#include "mage/input/input_key.h"
#include "mage/input/input_mouse.h"

#include "mage/layer/layer.h"
#include "mage/layer/layer_stack.h"

#include "mage/util/color.h"
#include "mage/util/dimensional.h"
#include "mage/util/functions.h"
#include "mage/util/positional.h"
#include "mage/util/typed.h"



// render api
#ifdef MAGE_RENDER_API_GL
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
	#include "platform/graphics/gl/buffer.h"
	#include "platform/graphics/gl/context.h"
	#include "platform/graphics/gl/core.h"
	#include "platform/graphics/gl/index_buffer.h"
	#include "platform/graphics/gl/vertex_array.h"
	#include "platform/graphics/gl/vertex_array_description.h"
	#include "platform/graphics/gl/vertex_buffer.h"
#endif



// os
#ifdef MAGE_PLATFORM_WINDOWS
	#include "platform/os/windows/windows_imgui_layer.h"
	#ifdef MAGE_BUILD_LIB
		#include "platform/os/windows/windows_input.h"
		#include "platform/os/windows/windows_window.h"
	#endif
#endif
