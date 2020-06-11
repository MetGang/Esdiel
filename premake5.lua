-- Workspace configuration
workspace "E+G Study Project"

    configurations {
        "Debug",
        "Release"
    }

    language "C++"
    cppdialect "C++17"

    defines {
        "SDL_MAIN_HANDLED"
    }

    flags {
        "LinkTimeOptimization"
    }

    filter "configurations:Debug"
        defines { "ESD_DEBUG" }
        optimize "Debug"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Full"

-- Main project
project "Esdiel"

    location "."

    kind "ConsoleApp"

    warnings "Extra"

    targetname "%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    targetdir "example"

    objdir "build/%{cfg.system}/%{cfg.buildcfg}/obj"

    files {
        "%{prj.location}/include/**.hpp",
        "%{prj.location}/source/**.cpp",
        "%{prj.location}/thirdparty/glad/glad.c"
    }

    includedirs {
        "%{prj.location}/include",
        "%{prj.location}/thirdparty/",
        "%{prj.location}/thirdparty/SDL2/include"
    }

    filter "system:windows"
        libdirs "%{prj.location}/thirdparty/SDL2/lib"

    links {
        "SDL2main",
        "SDL2"
    }
