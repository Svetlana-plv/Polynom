file(GLOB_RECURSE RUN_FILES *.cpp)

set(RunName "run")

add_executable(${RunName} ${RUN_FILES})
target_link_libraries(${RunName} PRIVATE ${ProjectName})