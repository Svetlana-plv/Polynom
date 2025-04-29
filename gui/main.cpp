#include <QApplication>
#include <QLabel>
#include <QStyleFactory>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    app.setStyle(QStyleFactory::create("Motif"));
    return app.exec();
}
