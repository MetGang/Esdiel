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

-- Global variables
targetDir = "%{cfg.system}/%{prj.name}/%{cfg.buildcfg}"

-- Main project
project "Esdiel"

    location "Esdiel"

    kind "WindowedApp"

    targetdir ("build/" .. targetDir .. "/bin")
    objdir ("build/" .. targetDir .. "/obj")

    files {
        "%{prj.location}/**.h",
        "%{prj.location}/**.hpp",
        "%{prj.location}/**.c",
        "%{prj.location}/**.cpp"
    }

    includedirs {
        "%{prj.location}/include",
        "%{prj.location}/thirdparty/",
        "%{prj.location}/thirdparty/SDL2/include"
    }

    libdirs {
        "%{prj.location}/thirdparty/SDL2/lib"
    }

    links {
        "SDL2main",
        "SDL2",
        "opengl32"
    }
