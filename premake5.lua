workspace "Uranium-Engine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Uranium-Engine"
    location "Uranium-Engine"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/%{prj.name}/" .. outputdir)
    objdir ("bin/%{prj.name}/" .. outputdir .. "-obj")

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.ixx",
        "%{prj.name}/**.cppm"
    }

    includedirs {
        "dependencies/glfw/include",
        "dependencies/glew/include",
        "dependencies/openal/include",
        "Uranium/vendor"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "UR_WINDOWS_PLATFORM"
        }
    
    filter "configurations:Debug"
        defines "UR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "UR_RELEASE"
        symbols "On"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/%{prj.name}/" .. outputdir)
    objdir ("bin/%{prj.name}/" .. outputdir .. "-obj")

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.ixx",
        "%{prj.name}/**.cppm"
    }

    includedirs {
        "dependencies/glfw/include",
        "dependencies/glew/include",
        "dependencies/openal/include"
    }

    links {
        "Uranium-Engine"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "UR_WINDOWS_PLATFORM"
        }

    filter "configurations:Debug"
        defines "UR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "UR_RELEASE"
        symbols "On"
