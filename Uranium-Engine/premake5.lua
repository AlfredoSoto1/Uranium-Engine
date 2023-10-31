project "Uranium-Engine"
    location "./"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/%{prj.name}/" .. output_binaries)
    objdir ("bin/%{prj.name}/" .. output_binaries .. "-int")

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.ixx",
        "%{prj.name}/**.cppm"
    }

    includedirs {
        "$(SolutionDir)Uranium-Engine/src",
        "$(SolutionDir)Uranium-Engine/vendor",
        "$(SolutionDir)dependencies/glfw/include",
        "$(SolutionDir)dependencies/glew/include",
        "d$(SolutionDir)ependencies/openal/include"
    }

    libdirs {
        "$(SolutionDir)dependencies/glfw/lib",
        "$(SolutionDir)dependencies/glew/lib",
        "$(SolutionDir)dependencies/openal/lib"
    }

    filter "system:windows"
        staticruntime "default"
        systemversion "latest"
        
        defines {
            "GLFW_STATIC",
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