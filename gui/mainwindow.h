 #pragma once

#include "tabwidget.h"
#include "database.h"

#include <QMainWindow>
#include <QWidget>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent* event);

private:
    int count = 0;
    Ui::MainWindow* ui;

    void addNewTab();
    void onTabChanged(int index);
    void saveAllToDataBase();
    void loadAllFromDatabase();
};

