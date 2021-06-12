# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("graphics-framework")

# Include sub-projects.
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "Build your own zlib")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build package with shared libraries.")
add_subdirectory ("thirdparty/assimp")
add_subdirectory ("thirdparty/DirectXTK")
add_subdirectory ("thirdparty/imgui-cmake")

add_subdirectory ("framework1")