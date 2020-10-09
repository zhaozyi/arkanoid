CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

set(VCPKG "" CACHE STRING "Locate the root directory of VCPKG.")

IF (WIN32)
    if (NOT VCPKG STREQUAL "" AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "${VCPKG}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    elseif (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
ENDIF ()

project(Arkanoid)

message("CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE}")

find_package(SDL2 REQUIRED)
if (NOT TARGET SDL2::SDL2)
    message("SDL2::SDL2 has not become a target before SDL 2.0.12")
    add_library(shim_SDL INTERFACE)
    target_include_directories(shim_SDL INTERFACE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(shim_SDL INTERFACE ${SDL2_LIBRARIES})
else()
    message("SDL2::SDL2 is a target now. We can use the modern syntax.")
    add_library(shim_SDL INTERFACE)
    target_link_libraries(shim_SDL INTERFACE SDL2::SDL2)
endif()

add_library(arkanoid_core STATIC
    src/Ball.cpp
    src/Brick.cpp
    src/Paddle.cpp
    src/Point.cpp
    src/World.cpp)

add_executable(arkanoid src/main.cpp)
target_link_libraries(arkanoid arkanoid_core shim_SDL)

add_executable(game src/game.cpp src/LTimer.cpp)
target_link_libraries(game arkanoid_core shim_SDL)
