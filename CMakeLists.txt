cmake_minimum_required(VERSION 3.25)
project(Analogsim VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set IMGUI_DIR to the path of the ImGui source directory
set(IMGUI_DIR libs/imgui)
include(FetchContent)

# Include the ImGui CMakeLists.txt
find_package(GLFW QUIET)

include_directories(include)

include_directories(libs/glfw/include)
add_subdirectory(libs/glfw)

#IMGUI

FetchContent_Populate(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)

set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL 3 REQUIRED)

add_library(imgui_glfw STATIC
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_glfw.h
        imgui/backends/imgui_impl_opengl3.h
)

target_link_libraries(imgui_glfw PUBLIC glfw ${OPENGL_LIBRARIES})

target_include_directories(imgui_glfw
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/imgui
        ${CMAKE_CURRENT_LIST_DIR}/imgui/backends
)

FetchContent_Declare(
        nfd
        GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git
)
FetchContent_MakeAvailable(nfd)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        Analogsim
        main.cpp
        main.h
        component.cpp
        component.h
        gui.h
        gui.cpp
        serializer.cpp
        serializer.h
        parts/sensor.cpp
        parts/sensor.h
        settings.h
        parts/plus.cpp
        parts/plus.h
        parts/dial.cpp
        parts/dial.h
        parts/plus.cpp
        parts/average.cpp
        parts/average.h
        parts.h
        parts/normalizePolygonA.cpp
        parts/normalizePolygonA.h
        parts/normalizePolygonB.cpp
        parts/normalizePolygonB.h
        parts/normalizePolygonC.cpp
        parts/normalizePolygonC.h
        include/nfd.h
        include/raymath.h
        parts/dotProduct.cpp
        parts/dotProduct.h
        parts/areaPolygon.cpp
        parts/areaPolygon.h
        Rectangle.h
        Rectangle.h
        Rectangle.cpp
)

# Include ImGui-related targets
target_link_libraries(Analogsim PRIVATE imgui_glfw nfd glfw)
