cmake_minimum_required(VERSION 3.25)
project(Analogsim VERSION 0.0.1)
include(FetchContent)

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



FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(include)
set(CMAKE_CXX_STANDARD 23)

add_executable(Analogsim main.cpp component.cpp component.h gui.h gui.cpp)

target_link_libraries(Analogsim raylib nlohmann_json::nlohmann_json)
