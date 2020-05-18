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

-- Project: Engine
project "Engine"

    location "Esdiel"

    kind "StaticLib"

    targetprefix "lib"
    targetname "engine"
    targetextension ".a"

    targetdir ("build/" .. targetDir .. "/lib")
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

-- Project: Game
project "Game"

    location "example"

    kind "WindowedApp"

    targetdir ("build/" .. targetDir .. "/bin")
    objdir ("build/" .. targetDir .. "/obj")

    files {
        "%{prj.location}/main.cpp"
    }

    includedirs {
        "%{wks.location}/Esdiel/include",
        "%{wks.location}/Esdiel/thirdparty/",
        "%{wks.location}/Esdiel/thirdparty/SDL2/include"
    }

    libdirs {
        "%{wks.location}/Esdiel/thirdparty/SDL2/lib"
    }

    links {
        "engine",
        "SDL2main",
        "SDL2",
        "opengl32"
    }
