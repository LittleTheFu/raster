cmake_minimum_required(VERSION 3.16)

project(raster)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third/sdl)
add_subdirectory(third/eigen)

add_executable(raster main.cpp sdlApp.cpp config.cpp frame.cpp)

target_include_directories(raster PRIVATE
    third/SDL/include
    third/eigen
)

target_link_libraries(raster SDL2-static)