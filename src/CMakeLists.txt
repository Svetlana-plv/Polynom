file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(${ProjectName} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_sources(${ProjectName} PRIVATE ${HEADER_FILES})

target_include_directories(${ProjectName} PUBLIC ${CMAKE_SOURCE_DIR}/src)