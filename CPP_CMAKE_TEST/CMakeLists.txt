cmake_minimum_required(VERSION 3.22)

project(GameName)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add preprocessor definitions based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DUR_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DUR_RELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Distribution")
    add_definitions(-DUR_DIST)
endif()

# Set library paths
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/lib/glfw")
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/lib/glad")
set(VULKAN_DIR "${CMAKE_SOURCE_DIR}/lib/vulkan")

# Include GLFW headers
include_directories("${GLFW_DIR}/include")
include_directories("${GLAD_DIR}/include")
include_directories("${VULKAN_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/include")

# Add all source files
set(GLAD_SOURCE "${GLAD_DIR}/src/glad.c")
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${GLAD_SOURCE})

# Set the static library path
set(GLFW_STATIC_LIB "${GLFW_DIR}/lib/glfw3.lib")
set(VULKAN_STATIC_LIB "${VULKAN_DIR}/lib/vulkan-1.lib")

# Link libraries (Windows libraries and OpenGL)
target_link_libraries(${CMAKE_PROJECT_NAME} 
    user32 
    gdi32 
    opengl32 
    shell32
    ${GLFW_STATIC_LIB}
    ${VULKAN_STATIC_LIB}
)

# Set specific flags for each configuration directly
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /Zi /Od /MDd)

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /MD /O2 /GS- /DNDEBUG)

elseif(CMAKE_BUILD_TYPE STREQUAL "Distribution")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /O2 /DNDEBUG /OPT:REF /INCREMENTAL:NO /MD)
endif()

# Apply linker flags for headless distribution builds
if(HEADLESS_DIST)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES 
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()
