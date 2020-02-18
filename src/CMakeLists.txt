cmake_minimum_required(VERSION 3.13)  # CMake version check
project(pathtracer)               # Create project "pathtracer"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}../../bin
)

set(SOURCE_FILES main.cpp Camera.cpp Color.cpp Material.cpp Ray.cpp Renderer.cpp Scene.cpp Skybox.cpp Sphere.cpp Triangle.cpp Object.cpp Rotation.cpp Plane.cpp)
include_directories(inc)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(main ${SOURCE_FILES})

target_link_libraries(main PRIVATE png PRIVATE pthread PUBLIC SDL2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")