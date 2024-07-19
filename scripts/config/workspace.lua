
root = "../../"
output_binaries = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

-- The workspace refers to the vs-solution name
workspace "Uranium-Engine"
    location (root)
    architecture "x64"
    configurations { "debug", "release", "dist" }
    startproject "production"
    
    filter "action:vs2022"
        defines { "UR_BUILD_VS2022", "UR_COMPILER_MSVC" }

    filter "action:gmake"
        defines { "UR_BUILD_GMAKE", "UR_COMPILER_GCC" }

-- Load the dependency paths
include "dependencies.lua"

-- Prepare and set the projects
include "../projects/setup-testing.lua"
include "../projects/setup-production.lua"

group "core"
    include "../projects/setup-core.lua"