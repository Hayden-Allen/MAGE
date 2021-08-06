#pragma once
// basic
#include <cmath>
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <thread>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <functional>
// platform
#ifdef MAGE_BUILD_LIB
	#ifdef MAGE_PLATFORM_WINDOWS
		#include <Windows.h>
		#include <glad/glad.h>
		#include <GLFW/glfw3.h>
		#include <GLFW/glfw3native.h>
		#include <imgui.h>
		#include <backends/imgui_impl_glfw.h>
		#include <backends/imgui_impl_opengl3.h>
	#endif
#endif
// vendor
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "mage/core.h"
#include "mage/log.h"
