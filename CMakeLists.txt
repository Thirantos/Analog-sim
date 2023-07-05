cmake_minimum_required(VERSION 3.25)
project(Analogsim VERSION 0.0.1)

set(RAYLIB_VERSION 4.5.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(raylib ${RAYLIB_VERSION} QUIET)

if (NOT raylib_FOUND)
    # Include CMake's FetchContent module to download and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()

include_directories(include)
set(CMAKE_CXX_STANDARD 17)

add_executable(Analogsim main.cpp component.cpp component.h)

target_link_libraries(Analogsim raylib)
