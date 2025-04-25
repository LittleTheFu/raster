cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project (raster)

add_subdirectory(third/sdl)

include_directories(
    third/SDL/include
    third/SDL/src
)

add_executable(raster main.cpp)
target_link_libraries(raster SDL2-static)