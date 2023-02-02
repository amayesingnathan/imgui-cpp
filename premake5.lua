include "dependencies/imgui"
include "dependencies/glfw"

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

    includedirs
    {
        "src",
        "dependencies/glfw/include",
        "dependencies/imgui",
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