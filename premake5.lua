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
IncludeDir ["glm"] = "Rise/vendor/glm"

include "Rise/vendor/GLFW"
include "Rise/vendor/Glad"
-- include "Rise/vendor/imgui" removed: upstream ocornut/imgui (docking branch)
-- has no premake5.lua, so ImGui can't build as its own project here.
-- Instead, its source is unity-built via Rise/src/Rise/ImGui/ImGuiBuild.cpp.

project "Rise"
    location "Rise"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rscph.h"
    pchsource "Rise/src/rscph.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs 
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
	    "GLFW",
        "Glad",
    -- "ImGui" removed: ImGui is no longer a separate premake project/lib.
    -- Since switching to the docking branch (which has no premake5.lua of its own),
    -- ImGui source is compiled directly into Rise via ImGuiBuild.cpp instead.
	    "opengl32.lib",
	    "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++17"     
        staticruntime "On"
        systemversion "latest"
        buildoptions { "/utf-8" }

        defines
        {
            "RS_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
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
    staticruntime "On"

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
        "Rise/src",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Rise"
    }

    filter "system:windows"
        cppdialect "C++17"     
        staticruntime "On"
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