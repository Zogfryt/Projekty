cmake_minimum_required(VERSION 3.17)
project(untitled3 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled3 main.c)
target_link_libraries(untitled3 -lOpenGL32 -lfreeGLUT)