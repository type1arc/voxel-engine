cmake_minimum_required(VERSION 3.20)
project(voxel-engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(OpenGL REQUIRED)
# Use a vendored GLAD (generated via glad CLI)
set(GLAD_DIR ${PROJECT_SOURCE_DIR}/third_party/glad)
add_library(glad STATIC
    ${GLAD_DIR}/src/gl.c
)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)
# Linux needs dl for dlsym in glad
if (UNIX AND NOT APPLE)
    target_link_libraries(glad PUBLIC dl)
endif()
# Use GLFW's CMake config if available (Arch package provides it)
find_package(glfw3 3.3 REQUIRED CONFIG)

# Target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/framework.cpp
    src/shader.cpp
)

# Include directories (add your own headers under include/)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Link libraries
# glfw target is provided by glfw3Config.cmake; GLEW and OpenGL are standard CMake packages
# No GLEW_STATIC define here; Arch typically links against shared GLEW.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        OpenGL::GL
        glad
        glfw
)

# On Linux, prefer RCC for high DPI / vsync handled in code.
