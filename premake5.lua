workspace "MAGE"
	architecture "x64"
	startproject "ORC"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}"

include "MAGE/vendor/COGA"
include "MAGE/vendor/hasl"

project "MAGE"
	location "MAGE"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MAGE/",
		"MAGE/src/",
		"MAGE/vendor/COGA/",
		"MAGE/vendor/COGA/src/",
		"MAGE/vendor/COGA/vendor/spdlog/include/",
		"MAGE/vendor/COGA/vendor/GLFW/include/",
		"MAGE/vendor/COGA/vendor/glad/include/",
		"MAGE/vendor/COGA/vendor/imgui/",
		"MAGE/vendor/COGA/vendor/glm"
	}

	links 
	{
		"hasl",
		"COGA"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"COGA_PLATFORM_WINDOWS",
			"COGA_RENDER_API_GL",
			"COGA_RAN=coga::gl",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines "COGA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "COGA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "COGA_DIST"
		runtime "Release"
		optimize "on"



project "ORC"
	location "ORC"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/",
		"%{prj.name}/src/",
		"MAGE/",
		"MAGE/src/",
		"MAGE/vendor/COGA/",
		"MAGE/vendor/COGA/src/",
		"MAGE/vendor/COGA/vendor/spdlog/include/",
		"MAGE/vendor/COGA/vendor/GLFW/include/",
		"MAGE/vendor/COGA/vendor/glad/include/",
		"MAGE/vendor/COGA/vendor/imgui/",
		"MAGE/vendor/COGA/vendor/glm"
	}

	links
	{
		"MAGE"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"COGA_PLATFORM_WINDOWS",
			"COGA_RENDER_API_GL",
			"COGA_RAN=coga::gl",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines "COGA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "COGA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "COGA_DIST"
		runtime "Release"
		optimize "on"