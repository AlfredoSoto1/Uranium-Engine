-- Define project
project "uranium"
    location (root.. "projects/%{prj.name}")
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    -- Output directories for object files and binaries
    objdir    (root.. "bin/intermediates/" .. output_binaries .. "/%{prj.name}")
    targetdir (root.. "bin/"               .. output_binaries .. "/%{prj.name}")

    -- Source files to include in the project
    files {
        root.. "projects/%{prj.name}/src/**.c",
        root.. "projects/%{prj.name}/src/**.h",
        root.. "projects/%{prj.name}/src/**.hpp",
        root.. "projects/%{prj.name}/src/**.cpp",
        root.. "projects/%{prj.name}/src/**.ixx",
        root.. "projects/%{prj.name}/src/**.cppm",
        root.. "projects/%{prj.name}/src/**.glsl",
    }
    -- Project define-specific
    filter { "kind:SharedLib" }
        defines { "UR_BUILD_DLL" }
    filter { "kind:StaticLib" }
        defines { "UR_BUILD_STATIC" }

    -- Include directories
    includedirs {
        root.. "projects/%{prj.name}/src",
    }

    -- Load all the dependencies to their corresponding platform
    setDependencies()

    -- Set default platform-specific configuration
    filter "system:windows"
        systemversion "latest"
        staticruntime "default"
        defines { "UR_PLATFORM_WINDOWS" }

    filter "system:linux"
        toolset "gcc" -- Use GCC as the toolset for Linux
        defines { "UR_PLATFORM_LINUX" }
        
    -- Set default build configurations
    setBuildConfigurations()