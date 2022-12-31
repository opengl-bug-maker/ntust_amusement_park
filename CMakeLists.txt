# let cmake.txt change to fix vs bug :O
cmake_minimum_required(VERSION 3.18)
project(AmusementPark)

set(CMAKE_CXX_STANDARD 17)

set( GLM_HOME include/glm)
set(GLAD_HOME include/glad)
set(SFML_HOME include/sfml/2.5.1_1)

link_directories("${SFML_HOME}/lib")
include_directories("src")
include_directories("src/Object")
include_directories("${GLAD_HOME}/include")
include_directories("${SFML_HOME}/include")
include_directories("${GLM_HOME}/include")

file(GLOB OBJECT_HEADER src/Object/*.h)
file(GLOB OBJECT_SOURCE src/Object/*.cpp)
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
        ${OBJECT_HEADER} ${OBJECT_SOURCE}
        ${CUSTOM-OBJECT_HEADER} ${CUSTOM-OBJECT_SOURCE}
        ${FERRIS_WHEEL_HEADER} ${FERRIS_WHEEL_SOURCE}
        ${OBJECT-COLLIDER_HEADER} ${OBJECT-COLLIDER_SOURCE}
        ${CAMERA_HEADER} ${CAMERA_SOURCE}
        ${Utilities_HEADER} ${Utilities_SOURCE}
        ${RenderUtilities_HEADER} ${RenderUtilities_SOURCE}
        )

target_link_libraries (AmusementPark
        sfml-graphics
        sfml-window
        sfml-system)

if (APPLE)
    target_link_libraries(AmusementPark "-framework OpenGL")
endif()