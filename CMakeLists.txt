cmake_minimum_required(VERSION 3.10)
project(SortingVisualization C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2TTF_LIBRARY_DIRS})


file(GLOB SRC_FILES src/*.c)

add_executable(sortviz ${SRC_FILES})

target_link_libraries(sortviz ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})
