workspace "MAGE"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}"

include "COGA/vendor/GLFW"
include "COGA/vendor/glad"
include "COGA/vendor/imgui"

project "COGA"
	location "COGA"
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
		"%{prj.name}/",
		"%{prj.name}/src/",
		"%{prj.name}/src/coga/",
		"%{prj.name}/vendor/spdlog/include/",
		"%{prj.name}/vendor/GLFW/include/",
		"%{prj.name}/vendor/glad/include/",
		"%{prj.name}/vendor/imgui/",
		"%{prj.name}/vendor/glm/"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"imgui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"COGA_PLATFORM_WINDOWS",
			"COGA_RENDER_API_GL",
			"COGA_RAN=coga::gl",
			"COGA_BUILD_LIB",
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
		"%{prj.name}/",
		"%{prj.name}/src/",
		"COGA/",
		"COGA/src/",
		"COGA/vendor/spdlog/include/",
		"COGA/vendor/GLFW/include/",
		"COGA/vendor/glad/include/",
		"COGA/vendor/imgui/",
		"COGA/vendor/glm"
	}

	links 
	{
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
		"COGA/",
		"COGA/src/",
		"COGA/vendor/spdlog/include/",
		"COGA/vendor/GLFW/include/",
		"COGA/vendor/glad/include/",
		"COGA/vendor/imgui/",
		"COGA/vendor/glm",
		"MAGE/src/"
	}

	links
	{
		"imgui",
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