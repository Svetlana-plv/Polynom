set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/QT/6.9.0/msvc2022_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(gui_translator
    main.cpp
    mainwindow.cpp
    mainwindow.h
    flowlayout.h
    flowlayout.cpp
    widgetpolynom.h
    widgetpolynom.cpp
    containerpolynom.h
    containerpolynom.cpp
    listpolynom.h
    listpolynom.cpp
    listlayout.h
    listlayout.cpp
    mainwindow.ui
    resources.qrc
)

target_link_libraries(gui_translator
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
