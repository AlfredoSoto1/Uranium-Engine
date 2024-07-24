
-- Compiler configurations
function setBuildConfigurations()
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        defines { "UR_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        symbols "on"
        defines { "UR_RELEASE" }

    filter "configurations:Dist"
        runtime "Release"
        optimize "on"
        symbols "off"
        defines { "UR_DISTRIBUTION" }
end