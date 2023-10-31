project "Uranium-Engine"
    location "./"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("../bin/%{prj.name}/" .. output_binaries)
    objdir ("../bin/%{prj.name}/" .. output_binaries .. "-int")

    files {
        "./**.h",
        "./**.hpp",
        "./**.cpp",
        "./**.ixx",
        "./**.cppm"
    }

    includedirs {
        "../Uranium-Engine/src",
        "../Uranium-Engine/vendor",
        "../dependencies/glfw/include",
        "../dependencies/glew/include",
        "../dependencies/openal/include"
    }

    libdirs {
        "../dependencies/glfw/lib",
        "../dependencies/glew/lib",
        "../dependencies/openal/lib"
    }

    filter "system:windows"
        staticruntime "default"
        systemversion "latest"
        
        defines {
            "GLEW_STATIC",
            "UR_WINDOWS_PLATFORM",
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        defines "UR_DEBUG"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        defines "UR_RELEASE"