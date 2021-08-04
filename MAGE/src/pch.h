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
#ifdef MAGE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
// vendor
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "mage/core.h"
