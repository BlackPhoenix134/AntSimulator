newoption 
{
   trigger = "opengl43",
   description = "use OpenGL 4.3"
}

workspace "AntSimulator"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "raylib"
		filter "configurations:Debug OR Release"
			kind "StaticLib"
			
		filter "action:vs*"
			defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
			characterset ("MBCS")
		
		filter "system:windows"
			defines{"_WIN32"}
			links {"winmm", "kernel32", "opengl32", "kernel32", "gdi32"}
		
		filter{}
		
		defines{"PLATFORM_DESKTOP"}
		if (_OPTIONS["opengl43"]) then
			defines{"GRAPHICS_API_OPENGL_43"}
		else
			defines{"GRAPHICS_API_OPENGL_33"}
		end
	
		location "vendor/raylib"
		language "C"
		targetdir ("bin/" .. outputdir .. "/AntSimulator")	
		
		includedirs { "vendor/raylib/src", "vendor/raylib/src/external/glfw/include"}
		vpaths 
		{
			["Header Files"] = { "vendor/raylib/src/**.h"},
			["Source Files/*"] = {"vendor/raylib/src/**.c"},
		}
		files {"vendor/raylib/src/*.h", "vendor/raylib/src/*.c"}


project "AntSimulator"
	location "AntSimulator"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files  
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"vendor/spdlog/include",
		"vendor/raylib/src",
		"vendor/mathfu/include/mathfu"
	}

	links {"raylib"}
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		dependson {"raylib"}
		links {"raylib.lib"}
        characterset ("MBCS")
		
	filter "system:windows"
		

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"
		defines{"_WIN32"}
		links {"winmm", "kernel32", "opengl32", "kernel32", "gdi32"}
		libdirs {"bin/" .. outputdir .. "/%{prj.name}"}

	filter "configurations:Debug"
		defines { "AS_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "AS_RELEASE" }
		symbols "On"