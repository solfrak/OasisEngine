cmake_minimum_required(VERSION 3.25)

project(OasisEngine
    VERSION 0.1.0
    DESCRIPTION "Oasis Game Engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Engine modules
add_subdirectory(engine/core)
add_subdirectory(engine/platform)

# Sandbox application
add_subdirectory(sandbox)
