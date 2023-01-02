# let cmake.txt change to fix vs bug :O
cmake_minimum_required(VERSION 3.18)
project(AmusementPark)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set( GLM_HOME include/glm)
set(GLAD_HOME include/glad)

include_directories("src")
include_directories("src/Object")
include_directories("${GLAD_HOME}/include")
include_directories("${GLM_HOME}/include")

#setting for SFML
if(CMAKE_HOST_APPLE)
    MESSAGE("OS: macOS")
    set(SFML_DIR "include/sfml/2.5.1-macOS/lib/cmake/SFML")
elseif(CMAKE_HOST_WIN32)
    MESSAGE("OS: Windows")
    set(SFML_DIR "include/sfml/2.5.1-windows/lib/cmake/SFML")
endif()
find_package(SFML REQUIRED COMPONENTS audio network graphics window system)
include_directories(${SFML_INCLUDE_DIR})
#end setting for sfml

file(GLOB OBJECT_HEADER src/Object/*.h)
file(GLOB OBJECT_SOURCE src/Object/*.cpp)
file(GLOB BASIC_OBJECT_HEADER src/Object/BasicObject/*.h)
file(GLOB BASIC_OBJECT_SOURCE src/Object/BasicObject/*.cpp)
file(GLOB OBJECT_PARTICLE_SOURCE src/Object/ParticleSystem/*.cpp)
file(GLOB OBJECT_PARTICLE_SOURCE src/Object/ParticleSystem/*.cpp)
file(GLOB FERRIS_WHEEL_HEADER src/Object/ferris_wheel/*.h)
file(GLOB FERRIS_WHEEL_SOURCE src/Object/ferris_wheel/*.cpp)
file(GLOB CUSTOM-OBJECT_HEADER src/Object/CustomObject/*.h)
file(GLOB CUSTOM-OBJECT_SOURCE src/Object/CustomObject/*.cpp)
file(GLOB OBJECT-COLLIDER_HEADER src/Object/Collider/*.h)
file(GLOB OBJECT-COLLIDER_SOURCE src/Object/Collider/*.cpp)
file(GLOB CAMERA_HEADER src/Camera/*.h)
file(GLOB CAMERA_SOURCE src/Camera/*.cpp)
file(GLOB Utilities_HEADER src/Utilities/*.h)
file(GLOB Utilities_SOURCE src/Utilities/*.cpp)
file(GLOB RenderUtilities_HEADER src/RenderUtilities/*.h)
file(GLOB RenderUtilities_SOURCE src/RenderUtilities/*.cpp)

add_executable(AmusementPark
        src/main.cpp
        include/glad.c
        src/GameWindow.cpp
        src/GameWindow.h
        ${OBJECT_SOURCE}
        ${BASIC_OBJECT_SOURCE}
        ${OBJECT_PARTICLE_SOURCE}
        ${CUSTOM-OBJECT_SOURCE}
        ${FERRIS_WHEEL_SOURCE}
        ${OBJECT-COLLIDER_SOURCE}
        ${CAMERA_SOURCE}
        ${Utilities_SOURCE}
        ${RenderUtilities_SOURCE}
        )

target_link_libraries(AmusementPark
        sfml-audio
        sfml-graphics
        sfml-window
        sfml-system)

if(CMAKE_HOST_APPLE)
    target_link_libraries(AmusementPark "-framework OpenGL")
endif()