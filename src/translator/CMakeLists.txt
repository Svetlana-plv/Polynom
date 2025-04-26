# Проверяем, есть ли файлы для сборки в папке translator
file(GLOB translator_srcs "*.cpp")
file(GLOB translator_hdrs "*.h*")

if(translator_srcs)
    # Создаем библиотеку translator (статическую)
    add_library(translator STATIC ${translator_srcs} ${translator_hdrs})
    
    # Подключаем include-директории
    target_include_directories(translator PUBLIC
        ${MP2_INCLUDE}
        ${MP2_INCLUDE}/translator
    )
    
    # Если есть зависимости, указываем их
    if(LIBRARY_DEPS)
        target_link_libraries(translator ${LIBRARY_DEPS})
    endif()
    
    # Делаем библиотеку доступной для родительского проекта
    set(TRANSLATOR_LIB translator PARENT_SCOPE)
    message(STATUS "Translator library configured")
else()
    message(WARNING "No source files found in translator directory")
endif()