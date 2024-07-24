-- Define project
project "production"
    location (root.. "projects/%{prj.name}")
    kind "ConsoleApp"
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
    -- defines { "UR_USE_DLL" }

    -- Include directories
    includedirs {
        root.. "projects/%{prj.name}/src",
        root.. "projects/uranium/src",
    }
    -- Linking with
    links {
        "uranium"
    }

    -- Load all the dependencies to their corresponding platform
    setDependencies()

    -- Set default platform-specific configuration
    filter "system:windows"
        systemversion "latest"
        staticruntime "default"
        defines {"UR_PLATFORM_WINDOWS"}

    filter "system:linux"
        toolset "gcc" -- Use GCC as the toolset for Linux
        defines { "UR_PLATFORM_LINUX" }
        
    -- Set default build configurations
    setBuildConfigurations()