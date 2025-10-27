cmake_minimum_required(VERSION 3.10)
project(SortingVisualization C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS} src)
link_directories(${SDL2_LIBRARY_DIRS})

file(GLOB SRC_FILES src/*.c)

add_executable(sortviz ${SRC_FILES})

target_link_libraries(sortviz ${SDL2_LIBRARIES})
