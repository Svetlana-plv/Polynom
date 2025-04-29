 #pragma once
#include "flowlayout.h"

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <Qlabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT


public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void addWidgetAnimation(QWidget* widget, FlowLayout* flow);

private:
    Ui::MainWindow* ui;


private slots:
    void on_pushButton_clicked();
    //void on_widget_clicked();
};

