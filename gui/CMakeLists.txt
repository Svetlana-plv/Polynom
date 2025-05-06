set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/QT/6.9.0/msvc2022_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

add_executable(gui_translator
    main.cpp

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    selectwidget.cpp
    selectwidget.h
    selectwidget.ui

    calculatorwidget.cpp
    calculatorwidget.h
    calculatorwidget.ui

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

    tabwidget.h
    tabwidget.cpp

    database.h
    database.cpp

    resources.qrc
)

target_link_libraries(gui_translator
    ${MP2_LIBRARY}
    Qt6::Sql
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
