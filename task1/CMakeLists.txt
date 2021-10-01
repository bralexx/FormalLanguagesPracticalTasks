cmake_minimum_required(VERSION 3.17)
project(task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(testsTask1 test_main.cpp solve.cpp solve.h)
add_executable(task1 main.cpp solve.cpp solve.h)
