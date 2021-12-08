cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
project(daily_leetcode)

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(test)