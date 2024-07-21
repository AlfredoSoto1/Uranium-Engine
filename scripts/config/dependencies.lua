
-- Define include and library directories
IncludeDirs = {
    GLFW   = root .. "dependencies/glfw/include",
    GLEW   = root .. "dependencies/glew/include",
    VULKAN = root .. "dependencies/vulkan/include",
    OPENAL = root .. "dependencies/openal/include",
    STB    = root .. "dependencies/stb/include"
}

LibraryDirs = {
    GLFW   = root .. "dependencies/glfw/lib",
    GLEW   = root .. "dependencies/glew/lib",
    VULKAN = root .. "dependencies/vulkan/lib",
    OPENAL = root .. "dependencies/openal/lib"
}

Libraries = {
    GLFW    = "glfw3",    
    VULKAN  = "vulkan-1", 
    GLEW    = "glew32s",  
    OPENGL  = "opengl32", 
    USER32  = "User32",   
    GDI32   = "Gdi32",    
    SHELL32 = "Shell32"  
}

function setDependencies()
    --  Define key to allow glew to be enabled for static linking
    defines "GLEW_STATIC"

    -- Configuration for Windows
    filter "system:windows"
        includedirs {
            IncludeDirs.GLFW,
            IncludeDirs.GLEW,
            IncludeDirs.VULKAN,
            IncludeDirs.OPENAL,
            IncludeDirs.STB
        }
        
        libdirs {
            LibraryDirs.GLFW,
            LibraryDirs.GLEW,
            LibraryDirs.VULKAN,
            LibraryDirs.OPENAL
        }

        links {
            Libraries.GLFW,
            Libraries.VULKAN,
            Libraries.GLEW,
            Libraries.OPENGL,
            Libraries.USER32,
            Libraries.GDI32,
            Libraries.SHELL32
        }
end