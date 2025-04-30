cmake_minimum_required(VERSION 3.16)

project(raster)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third/assimp)
add_subdirectory(third/lodepng)
add_subdirectory(third/sdl)

# 禁用 Eigen 自带的测试
set(BUILD_TESTING OFF CACHE BOOL "Disable Eigen tests")

# 添加 Eigen 子目录
add_subdirectory(third/eigen)

add_executable(raster 
    main.cpp 
    sdlApp.cpp
    config.cpp 
    frame.cpp
    camera.cpp 
    triangle.cpp
    scene.cpp 
    pipeline.cpp
    vertex.cpp
    vertexBuffer.cpp
    mesh.cpp
    zbuffer.cpp
    texture.cpp)

target_include_directories(raster PRIVATE
    third/SDL/include
    third/eigen
    third/lodepng/include
    ${PROJECT_SOURCE_DIR}/third/assimp/include
    ${CMAKE_CURRENT_BINARY_DIR}/third/assimp/include
)

target_link_libraries(raster SDL2-static)
target_link_libraries(raster lodepng)
target_link_libraries(raster assimp)


# 添加 googletest 本地目录
add_subdirectory(third/googletest)

# 启用测试
enable_testing()

# 添加你的可执行文件
add_executable(my_test test.cpp)

target_include_directories(my_test PRIVATE
    third/eigen
)

# 链接 gtest 和 gtest_main（或 gmock，如有需要）
target_link_libraries(my_test
    gtest
    gtest_main
)

add_test(NAME MyTest COMMAND my_test)