cmake_minimum_required(VERSION 3.13)  # CMake version check
project(pathtracer)               # Create project "pathtracer"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

add_link_options("-lpng")

set(SOURCE_FILES main.cpp Camera.cpp Color.cpp Material.cpp Ray.cpp Renderer.cpp Scene.cpp Skybox.cpp Sphere.cpp Triangle.cpp Object.cpp Rotation.cpp inc/Rotation.h Plane.cpp inc/Plane.h)

include_directories(inc)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(path_tracer ${SOURCE_FILES})