workspace "AntSimulator"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

	platforms 
	{ 
		"Win64"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AntSimulator"
	location "AntSimulator"
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
		"%{prj.name}/vendor/spdlog/include"
	}



	filter "platforms:Win64"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"

	filter "configurations:Debug"
		defines { "AS_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "AS_RELEASE" }
		symbols "On"

	filter "configurations:Dist"
		defines { "AS_DIST" }
		symbols "On"