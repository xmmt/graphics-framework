cmake_minimum_required (VERSION 3.8)

project ("imgui-cmake")

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    ../imgui/imgui.cpp
    ../imgui/imgui_demo.cpp
    ../imgui/imgui_draw.cpp
    ../imgui/imgui_tables.cpp
    ../imgui/imgui_widgets.cpp
    ../imgui/backends/imgui_impl_win32.cpp
    ../imgui/backends/imgui_impl_dx11.cpp
)

add_library (${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ../imgui ../imgui/backends)