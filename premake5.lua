workspace "Rise"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir ["GLFW"] = "Rise/vendor/GLFW/include"
IncludeDir ["Glad"] = "Rise/vendor/Glad/include"

include "Rise/vendor/GLFW"
include "Rise/vendor/Glad"

project "Rise"
    location "Rise"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rscph.h"
    pchsource "Rise/src/rscph.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    links
    {
	    "GLFW",
        "Glad",
	    "opengl32.lib",
	    "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++17"     
        staticruntime "Off"
        systemversion "latest"
        buildoptions { "/utf-8" }

        defines
        {
            "RS_PLATFORM_WINDOWS",
            "RS_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") 
        }

    filter "configurations:Debug"
        defines "RS_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "RS_RELEASE"
        buildoptions "/MD"
        optimize "On"          

    filter "configurations:Dist"
        defines "RS_DIST"
        buildoptions "/MD"
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
        "Rise/vendor/spdlog/include",
        "Rise/src"
    }

    links
    {
        "Rise"
    }

    filter "system:windows"
        cppdialect "C++17"     
        staticruntime "Off"
        systemversion "latest"
        buildoptions { "/utf-8" }

        defines
        {
            "RS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "RS_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "RS_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "RS_DIST"
        buildoptions "/MD"
        optimize "On"