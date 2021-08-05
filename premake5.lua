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
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "MAGE/src/pch.cpp"

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
		"%{prj.name}/vendor/glm"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"imgui"
	}

	filter "system:windows"
		cppdialect "C++latest"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MAGE_PLATFORM_WINDOWS",
			"MAGE_BUILD_DLL",
			"_CRT_SECURE_NO_WARNINGS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir .. "/ORC")
		}

	filter "configurations:Debug"
		defines "MAGE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "MAGE_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "MAGE_DIST"
		buildoptions "/MD"
		optimize "On"



project "ORC"
	location "ORC"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "ORC/src/pch.cpp"

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
		"MAGE/vendor/imgui/include/",
		"MAGE/vendor/glm"
	}

	links
	{
		"MAGE"
	}

	filter "system:windows"
		cppdialect "C++latest"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MAGE_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines "MAGE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "MAGE_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "MAGE_DIST"
		buildoptions "/MD"
		optimize "On"