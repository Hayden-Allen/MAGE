workspace "MAGE"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}"

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
		"%{prj.name}/vendor/spdlog/include/"
	}

	filter "system:windows"
		cppdialect "C++latest"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MAGE_PLATFORM_WINDOWS",
			"MAGE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir .. "/ORC")
		}

	filter "configurations:Debug"
		defines "MAGE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "MAGE_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "MAGE_DIST"
		optimize "On"



project "ORC"
	location "ORC"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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
		"MAGE/vendor/spdlog/include/"
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
			"MAGE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MAGE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "MAGE_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "MAGE_DIST"
		optimize "On"