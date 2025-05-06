 #include <QApplication>
#include <QLabel>
#include <QStyleFactory>
#include <QMessageBox>

#include "mainwindow.h" 
#include "tabwidget.h"
#include "database.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    if (!DatabaseManager::initDatabase()) {
        QMessageBox::critical(nullptr, "error", "cannot to connect a database.");
        return -1;
    }

    MainWindow w;
    w.show();

    app.setStyle(QStyleFactory::create("SimpleStyle"));
    return app.exec();
}

 