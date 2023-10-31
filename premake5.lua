workspace "Uranium-Engine"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

output_binaries = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "SandBox-Game"
include "Uranium-Engine"