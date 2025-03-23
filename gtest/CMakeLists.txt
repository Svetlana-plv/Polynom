cmake_minimum_required(VERSION 3.15)

project(GTest)

add_library(gtest STATIC gtest-all.cc)
target_include_directories(gtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})