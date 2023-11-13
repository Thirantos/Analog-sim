cmake_minimum_required(VERSION 3.25)
project(Analogsim VERSION 0.0.1)
include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

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


add_executable(Analogsim src/main.cpp src/main.h src/component.cpp src/component.h src/gui.h src/gui.cpp src/serializer.cpp src/serializer.h src/parts/sensor.cpp src/parts/sensor.h src/settings.h src/parts/plus.cpp src/parts/plus.h src/parts/dial.cpp src/parts/dial.h src/parts/plus.cpp src/parts/average.cpp src/parts/average.h src/parts.h
        src/parts/normalizePolygon.cpp
        src/parts/normalizePolygon.h
        include/nfd.h
        include/rlImGui.cpp
        include/rlImGui.h
        include/rlImGuiColors.h
        include/RaylibSerialize.hpp
        src/parts/dotProduct.cpp
        src/parts/dotProduct.h
        src/parts/areaPolygon.cpp
        src/parts/areaPolygon.h
        src/parts/combineVector.cpp
        src/parts/combineVector.h
        src/parts/combineVector.h
        src/parts/separateVector.cpp
        src/parts/separateVector.h
        src/parts/separateVector.h
        src/parts/vectorBetweenVectors.cpp
        src/parts/vectorBetweenVectors.h
        src/parts/vectorBetweenVectors.h
        src/parts/projectVector.cpp
        src/parts/projectVector.h
        src/parts/c24.cpp
        src/parts/c24.h
        src/parts/middlePolygon.cpp
        src/parts/middlePolygon.h
        src/parts/scaleVector.cpp
        src/parts/scaleVector.h
        src/parts/scaleVector.h
        src/matrix.cpp
        src/matrix.h
        src/parts/matrixKernel.cpp
        src/parts/matrixKernel.h
)
#target_compile_options(Analogsim PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(Analogsim PRIVATE raylib nfd imgui_glfw)
