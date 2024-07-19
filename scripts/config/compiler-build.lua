
-- Compiler configurations
filter "configurations:debug"
    runtime "debug"
    symbols "on"
    defines { "UR_DEBUG" }

filter "configurations:release"
    runtime "release"
    optimize "on"
    symbols "on"
    defines { "UR_RELEASE" }

filter "configurations:dist"
    runtime "release"
    optimize "on"
    symbols "off"
    defines { "UR_DISTRIBUTION" }