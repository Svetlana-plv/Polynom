#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flowlayout.h"
#include "widgetpolynom.h"
#include "ContainerPolynom.h"
#include "listpolynom.h"

#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QWidget* old = ui->scrollArea->takeWidget();
    QWidget* old1 = ui->scrollArea_2->takeWidget();
    delete old;
    delete old1;

    auto* container = new ContainerPolynom();
    auto* containerList = new listPolynom();
    ui->scrollArea->setWidget(container);
    ui->scrollArea_2->setWidget(containerList);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    auto flow = static_cast<FlowLayout*>(ui->scrollArea->widget()->layout());
    auto widgetP = new widgetPolynom();
    flow->addWidget(widgetP);
}

