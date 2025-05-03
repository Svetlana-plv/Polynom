 #include <QApplication>
#include <QLabel>
#include <QStyleFactory>

#include "mainwindow.h" 
#include "tabwidget.h"


int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    app.setStyle(QStyleFactory::create("SimpleStyle"));
    return app.exec();
}

 