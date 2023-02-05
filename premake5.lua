workspace "imgui-cpp"

    configurations 
    { 
        "Debug",
        "Release"
    }
    
    platforms
    {
        "x64",
        "ARM32",
        "ARM64"
    }

	filter "platforms:x64"
		architecture "x86_64"

	filter "platforms:ARM32"
		architecture "ARM"

 	filter "configurations:ARM64"
		architecture "ARM64"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["imguicpp"] 	= "%{wks.location}/imgui-cpp/src"
IncludeDir["imgui"] 	= "%{wks.location}/dependencies/imgui"
IncludeDir["glfw"] 	= "%{wks.location}/dependencies/glfw/include"

group "Dependencies"
	include "dependencies/imgui"
	include "dependencies/glfw"
group ""

project "imgui-cpp"
    language "C++"
    cppdialect "C++20"
		
    targetdir 	("%{wks.location}/bin/%{prj.name}/" .. outputDir)
    objdir 		("%{wks.location}/obj/%{prj.name}/" .. outputDir)

    files 
    { 
        "src/**.h", 
        "src/**.cpp",
        "src/**.hxx", 
        "src/**.ixx",
        "src/**.ixxp",
    }
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

<<<<<<< Updated upstream
=======
	IncludeDir["imgui"] 	= "%{prj.location}/dependencies/imgui"
	IncludeDir["glfw"] 	= "%{prj.location}/dependencies/glfw/include"
>>>>>>> Stashed changes
    includedirs
    {
        "src",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glfw}",
    }

	links
	{
		"imgui",
		"glfw",
	}
    
    filter { "files:**.ixx" }
        compileas "Module"
        
    filter { "files:**.ixxp" }
        compileas "ModulePartition"
		
    filter "system:windows"
        kind "StaticLib"
        staticruntime "off"
        systemversion "latest"
		
	filter "system:linux"
        kind "SharedLib"
        staticruntime "off"
        pic "On"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
        symbols "on"
    filter "configurations:Release"
		runtime "Release"
        optimize "on"