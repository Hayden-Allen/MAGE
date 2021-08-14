workspace "MAGE"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}"

include "MAGE/vendor/GLFW"
include "MAGE/vendor/glad"
include "MAGE/vendor/imgui"

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
		"%{prj.name}/src/mage/",
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
			"MAGE_PLATFORM_WINDOWS",
			"MAGE_RENDER_API_GL",
			"MAGE_RAN=mage::gl",
			"MAGE_BUILD_LIB",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "MAGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MAGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MAGE_DIST"
		runtime "Release"
		optimize "on"



project "N"
	location "N"
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
		"MAGE/",
		"MAGE/src/",
		"MAGE/vendor/spdlog/include/",
		"MAGE/vendor/GLFW/include/",
		"MAGE/vendor/glad/include/",
		"MAGE/vendor/imgui/",
		"MAGE/vendor/glm"
	}

	links 
	{
		"MAGE"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MAGE_PLATFORM_WINDOWS",
			"MAGE_RENDER_API_GL",
			"MAGE_RAN=mage::gl",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines "MAGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MAGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MAGE_DIST"
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
		"MAGE/vendor/spdlog/include/",
		"MAGE/vendor/GLFW/include/",
		"MAGE/vendor/glad/include/",
		"MAGE/vendor/imgui/",
		"MAGE/vendor/glm",
		"N/src/"
	}

	links
	{
		"imgui",
		"N"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MAGE_PLATFORM_WINDOWS",
			"MAGE_RENDER_API_GL",
			"MAGE_RAN=mage::gl",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines "MAGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MAGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MAGE_DIST"
		runtime "Release"
		optimize "on"