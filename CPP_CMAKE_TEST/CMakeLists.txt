# Minimum CMake version required
cmake_minimum_required(VERSION 3.22)

# Define the project name
project(CPP_CMAKE_TEST)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source directory and gather all source files
set(SOURCE_DIR "src")
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

# Ensure that source files are found
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in ${SOURCE_DIR}")
endif()

# Ensure the 'include' directory exists if you need headers
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
if(EXISTS "${INCLUDE_DIR}")
    include_directories(${INCLUDE_DIR})
else()
    message(STATUS "Include directory not found, skipping include setup.")
endif()

# Define the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

if(HEADLESS_DIST)
    # Set properties for the linker to hide the console window
    # This linking flags only apply to the msvc compiler ONLY.
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    message(STATUS "Linker flags applied to hide console window.")
endif()

# Optional: Link math library (if necessary)
# target_link_libraries(${CMAKE_PROJECT_NAME} m)
