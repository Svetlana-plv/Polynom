 #pragma once

#include "tabwidget.h"

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

private:

    Ui::MainWindow* ui;

    void addNewTab();
    void onTabChanged(int index);
};

