cmake_minimum_required(VERSION 3.5)

project(rpg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rpg main.cpp
    engine/renderer.cpp
    engine/camera.cpp
    engine/movable.cpp
    engine/mesh.cpp
    engine/drawable.cpp
    engine/texture.cpp
)

target_link_libraries(rpg
    GL
    GLEW
    glut
    freeimage
    assimp
)
