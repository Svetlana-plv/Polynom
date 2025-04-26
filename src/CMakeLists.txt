set(target ${MP2_LIBRARY})

# Основные исходные файлы
file(GLOB hdrs "*.h*" "${MP2_INCLUDE}/*.h*" "${MP2_INCLUDE}/translator/*.h*")
file(GLOB srcs "*.cpp")

# Добавляем файлы из папки translator (если она существует)
if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/translator")
    file(GLOB translator_srcs "translator/*.cpp")
    list(APPEND srcs ${translator_srcs})
endif()

if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/translator")
    add_subdirectory(translator)
    list(APPEND LIBRARY_DEPS ${TRANSLATOR_LIB})
endif()

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})

# Добавляем include директорию translator (уже добавлено в корневом CMakeLists.txt)