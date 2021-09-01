#pragma once
#include "pch.h"



// engine
#include "mage/application.h"
#include "mage/timestep.h"
#include "mage/window.h"

#include "mage/event/app_event.h"
#include "mage/event/event.h"
#include "mage/event/event_handler.h"
#include "mage/event/event_propagator.h"
#include "mage/event/key_event.h"
#include "mage/event/mouse_event.h"
#include "mage/event/window_event.h"

#include "mage/graphics/buffer.h"
#include "mage/graphics/camera.h"
#include "mage/graphics/context.h"
#include "mage/graphics/framebuffer.h"
#include "mage/graphics/framebuffer_attachment.h"
#include "mage/graphics/render_object.h"
#include "mage/graphics/renderer.h"
#include "mage/graphics/retained_buffer.h"
#include "mage/graphics/retained_texture.h"
#include "mage/graphics/shader.h"
#include "mage/graphics/shader_preprocessor.h"
#include "mage/graphics/shader_program.h"
#include "mage/graphics/shader_type.h"
#include "mage/graphics/texture.h"
#include "mage/graphics/vertex_array.h"
#include "mage/graphics/vertex_array_description.h"

#include "mage/imgui/dockspace.h"
#include "mage/imgui/layer.h"
#include "mage/imgui/window.h"

#include "mage/io/file.h"
#include "mage/io/input.h"
#include "mage/io/input_key.h"
#include "mage/io/input_mouse.h"
#include "mage/io/serializable.h"

#include "mage/layer/layer.h"
#include "mage/layer/layer_stack.h"

#include "mage/util/bank.h"
#include "mage/util/color.h"
#include "mage/util/dimensional.h"
#include "mage/util/functions.h"
#include "mage/util/indexed_list.h"
#include "mage/util/iterable.h"
#include "mage/util/movable.h"
#include "mage/util/point.h"
#include "mage/util/positional.h"
#include "mage/util/range.h"
#include "mage/util/rect.h"
#include "mage/util/rect_packer.h"
#include "mage/util/stateful.h"
#include "mage/util/typed.h"



// render api
#ifdef MAGE_RENDER_API_GL
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
	#include "platform/graphics/gl/buffer.h"
	#include "platform/graphics/gl/camera.h"
	#include "platform/graphics/gl/context.h"
	#include "platform/graphics/gl/framebuffer.h"
	#include "platform/graphics/gl/framebuffer_attachment.h"
	#include "platform/graphics/gl/index_buffer.h"
	#include "platform/graphics/gl/retained_buffer.h"
	#include "platform/graphics/gl/retained_index_buffer.h"
	#include "platform/graphics/gl/retained_texture.h"
	#include "platform/graphics/gl/retained_vertex_buffer.h"
	#include "platform/graphics/gl/shader.h"
	#include "platform/graphics/gl/shader_program.h"
	#include "platform/graphics/gl/shader_type.h"
	#include "platform/graphics/gl/texture.h"
	#include "platform/graphics/gl/vertex_array.h"
	#include "platform/graphics/gl/vertex_buffer.h"
#endif



// os
#ifdef MAGE_PLATFORM_WINDOWS
	#include "platform/os/windows/windows_layer.h"
	#ifdef MAGE_BUILD_LIB
		#include "platform/os/windows/windows_input.h"
		#include "platform/os/windows/windows_window.h"
	#endif
#endif