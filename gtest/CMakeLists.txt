cmake_minimum_required(VERSION 3.14)
project(gtest)

# Собираем GTest
add_library(gtest STATIC src/gtest-all.cc)
target_include_directories(gtest PUBLIC include)

add_library(gtest_main STATIC src/gtest_main.cc)
target_link_libraries(gtest_main gtest)