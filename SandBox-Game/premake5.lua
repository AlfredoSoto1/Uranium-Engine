project "SandBox-Game"
    location "./"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("../bin/%{prj.name}/" .. output_binaries)
    objdir ("../bin/%{prj.name}/" .. output_binaries .. "-int")

    files {
        "./**.h",
        "./**.hpp",
        "./**.cpp",
        "./**.ixx",
        "./**.cppm",
        "./**.glsl",
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

    links {
        "Uranium-Engine",
        "glew32s",
        "glfw3",
        "opengl32",
        "User32",
        "Gdi32",
        "Shell32",
        "OpenAL32"
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