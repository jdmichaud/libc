cmake_minimum_required(VERSION 3.20)
project(libc C)

set(CMAKE_C_STANDARD 99)

add_library(c src/libc.c)
target_compile_options(c PUBLIC -nostdlib)

add_executable(test test/test.c)
target_link_libraries(test c "-nostdlib")

