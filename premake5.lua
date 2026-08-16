workspace "Rise"
    architecture "x64"
    startproject "Sandbox"
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
IncludeDir ["ImGui"] = "Rise/vendor/imgui"

include "Rise/vendor/GLFW"
include "Rise/vendor/Glad"
include "Rise/vendor/imgui"

project "Rise"
    location "Rise"
    kind "SharedLib"
    language "C++"
    staticruntime "Off"

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
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
	    "GLFW",
        "Glad",
        "ImGui",
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
            "GLFW_INCLUDE_NONE",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") 
        }

    filter "configurations:Debug"
        defines "RS_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RS_RELEASE"
        runtime "Release"
        optimize "On"          

    filter "configurations:Dist"
        defines "RS_DIST"
        runtime "Release"
        optimize "On"         

project "Sandbox"
    location "Sandbox"      
    kind "ConsoleApp"
    language "C++"
    staticruntime "Off"

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
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RS_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "RS_DIST"
        runtime "Release"
        optimize "On"