cmake_minimum_required(VERSION 3.15)

set(ProjectName "Polynom")

project(${ProjectName})

include_directories(include)

add_subdirectory(gtest)
add_subdirectory(run)
add_subdirectory(src)
add_subdirectory(test)