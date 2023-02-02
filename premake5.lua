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
IncludeDir["imgui"] 	= "%{wks.location}/imgui-cpp/dependencies/imgui"

include "imgui-cpp"