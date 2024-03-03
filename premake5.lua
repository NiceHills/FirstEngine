workspace "FirstEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "FirstEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "FirstEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "FirstEngine/vendor/imgui"
IncludeDir["glm"] = "FirstEngine/vendor/glm"


include "FirstEngine/vendor/GLFW"
include "FirstEngine/vendor/Glad"
include "FirstEngine/vendor/imgui"



project "FirstEngine"
	location "FirstEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fepch.h"
	pchsource "FirstEngine/src/fepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"

	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS",
			"FE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		postbuildcommands
		{
			{"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
		}

	filter "configurations:Debug"
		defines "FE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FE_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"FirstEngine/vendor/spdlog/include",
		"FirstEngine/src",
		"FirstEngine/vendor",
		"%{IncludeDir.glm}"

	}

	links
	{
		"FirstEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "FE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FE_DIST"
		runtime "Release"
		optimize "On"