cmake_minimum_required(VERSION 3.25)
project(Analogsim VERSION 0.0.1)
include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(raylib ${RAYLIB_VERSION} QUIET)
find_package(imgui_glfw QUIET)


if (NOT raylib_FOUND)
    include(FetchContent)
    # Include CMake's FetchContent module to download and build raylib

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif ()

if(NOT imgui_glfw_FOUND)
    FetchContent_Populate(imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui
    )

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends)

    set(OpenGL_GL_PREFERENCE "LEGACY")
    find_package(OpenGL 3 REQUIRED)

    add_library(imgui_glfw STATIC
            libs/imgui/imgui.cpp
            libs/imgui/imgui_draw.cpp
            libs/imgui/imgui_demo.cpp
            libs/imgui/imgui_tables.cpp
            libs/imgui/imgui_widgets.cpp
            libs/imgui/backends/imgui_impl_glfw.cpp
            libs/imgui/backends/imgui_impl_opengl3.cpp
            libs/imgui/backends/imgui_impl_glfw.h
            libs/imgui/backends/imgui_impl_opengl3.h
    )

    target_link_libraries(imgui_glfw PUBLIC glfw ${OPENGL_LIBRARIES})

    target_include_directories(imgui_glfw
            PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/libs/imgui
            ${CMAKE_CURRENT_LIST_DIR}/libs/imgui/backends
    )
endif ()

include_directories(include include/rllmgui)
add_subdirectory(libs/nativefiledialog-extended)
set(CMAKE_CXX_STANDARD 23)

add_executable(Analogsim src/main.cpp src/main.h src/component.cpp src/component.h src/gui.h src/gui.cpp src/serializer.cpp src/serializer.h src/parts/sensor.cpp src/parts/sensor.h src/settings.h src/parts/plus.cpp src/parts/plus.h src/parts/dial.cpp src/parts/dial.h src/parts/plus.cpp src/parts/average.cpp src/parts/average.h src/parts.h
        src/parts/normalizePolygonA.cpp
        src/parts/normalizePolygonA.h
        src/parts/normalizePolygonB.cpp
        src/parts/normalizePolygonB.h
        src/parts/normalizePolygonC.cpp
        src/parts/normalizePolygonC.h
        include/nfd.h
        include/rlImGui.cpp
        include/rlImGui.h
        include/rlImGuiColors.h
        src/parts/dotProduct.cpp
        src/parts/dotProduct.h
        src/parts/areaPolygon.cpp
        src/parts/areaPolygon.h
)
#target_compile_options(Analogsim PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(Analogsim PRIVATE raylib nfd imgui_glfw)
