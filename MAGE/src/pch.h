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
#if defined(MAGE_PLATFORM_WINDOWS) && defined(MAGE_BUILD_DLL)
	#include <Windows.h>
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
	#include <GLFW/glfw3native.h>
#endif
// vendor
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "mage/core.h"
