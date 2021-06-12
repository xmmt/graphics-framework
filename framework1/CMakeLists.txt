# CMakeList.txt : CMake project for framework1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(framework1)

# find_package(assimp REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    source/main.cpp
)

add_executable (${PROJECT_NAME} WIN32 ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} imgui-cmake assimp DirectXTK d3d11 dxgi d3dcompiler dxguid)

# TODO: Add tests and install targets if needed.
