cmake_minimum_required(VERSION 3.25)
project(Analogsim VERSION 0.0.1)
include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(raylib ${RAYLIB_VERSION} QUIET)


if (NOT raylib_FOUND)
    include(FetchContent)
    # Include CMake's FetchContent module to download and build raylib

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif ()

include_directories(include)
add_subdirectory(libs/nativefiledialog-extended)
set(CMAKE_CXX_STANDARD 23)

add_executable(Analogsim main.cpp main.h component.cpp component.h gui.h gui.cpp serializer.cpp serializer.h parts/sensor.cpp parts/sensor.h settings.h parts/plus.cpp parts/plus.h parts/dial.cpp parts/dial.h parts/plus.cpp parts/average.cpp parts/average.h parts.h
        parts/normalizePolygonA.cpp
        parts/normalizePolygonA.h
        parts/normalizePolygonB.cpp
        parts/normalizePolygonB.h
        parts/normalizePolygonC.cpp
        parts/normalizePolygonC.h
        include/nfd.h
        parts/dotProduct.cpp
        parts/dotProduct.h
        parts/areaPolygon.cpp
        parts/areaPolygon.h
)
#target_compile_options(Analogsim PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(Analogsim PRIVATE raylib nfd)
