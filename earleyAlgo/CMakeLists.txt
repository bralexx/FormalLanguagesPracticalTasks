cmake_minimum_required(VERSION 3.17)
project(earleyAlgo)

set(CMAKE_CXX_STANDARD 14)

add_executable(earleyAlgo main.cpp Grammar.cpp Grammar.h)

add_subdirectory(googletest-master)
add_executable(tests test_main.cpp Grammar.cpp Grammar.h)
target_link_libraries(tests gtest)