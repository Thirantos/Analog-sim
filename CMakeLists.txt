cmake_minimum_required(VERSION 3.25)
project(Analogsim VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set IMGUI_DIR to the path of the ImGui source directory
set(IMGUI_DIR libs/imgui)
include(FetchContent)
include(ExternalProject)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Include the ImGui CMakeLists.txt
find_package(GLFW QUIET)
find_package(imgui_glfw QUIET)



include_directories(include libs/glfw/include)



add_subdirectory(libs/glfw libs/glew)


# Define the GLEW version and URL
set(GLEW_VERSION "2.1.0")




#IMGUI
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

add_subdirectory(libs/nativefiledialog-extended)



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
        include/nanovg/nanovg_gl.h
        include/nanovg/nanovg.h

        parts/dotProduct.cpp
        parts/dotProduct.h
        parts/areaPolygon.cpp
        parts/areaPolygon.h
        functions.h
        functions.h
        functions.cpp
        colours.h
        include/nanovg/nanovg.c
)

# Include ImGui-related targets
target_link_libraries(Analogsim PRIVATE imgui_glfw nfd glfw GL glew)
