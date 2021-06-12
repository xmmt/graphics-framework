# CMakeList.txt : CMake project for framework1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(framework1)

set(CMAKE_CXX_STANDARD 20)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

set(SOURCES
    source/Display.cpp
    source/Game.cpp
    source/GameComponent.cpp
    source/InputDevice.cpp
    source/Material.cpp
    source/Renderer.cpp
    source/Shader.cpp
    source/Source.cpp
    source/TriangleComponent.cpp
    source/Triangles.cpp
    source/Utils.cpp

    source/DisplayWin32.cpp
    source/RendererDirectX.cpp
)

add_executable (${PROJECT_NAME} WIN32 ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

set(LIBRARIES
    imgui-cmake
    assimp
    DirectXTK
    d3d11
    dxgi
    d3dcompiler
    dxguid
)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# TODO: Add tests and install targets if needed.
