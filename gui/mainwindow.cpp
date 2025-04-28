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
    //auto flow = static_cast<FlowLayout*>(ui->scrollArea->widget()->layout());
    auto widgetP = new widgetPolynom();
    addWidgetAnimation(widgetP);
}

void MainWindow::addWidgetAnimation(QWidget* widget)
{
    auto widgetP = qobject_cast<widgetPolynom*>(widget);
    if (!widgetP) return;

    auto flow = static_cast<FlowLayout*>(ui->scrollArea->widget()->layout());
    if (!flow) return;


    flow->addWidget(widgetP);


    auto anim = new QPropertyAnimation(widgetP, "maximumWidth", this);
    anim->setDuration(1000);
    anim->setStartValue(0);
    anim->setEndValue(400);
    anim->setEasingCurve(QEasingCurve::OutCubic); // Пружинистый эффект

    auto* effect = new QGraphicsOpacityEffect(widgetP);
    widgetP->setGraphicsEffect(effect);
    QPropertyAnimation* fadeAnim = new QPropertyAnimation(effect, "opacity");
    fadeAnim->setDuration(300);
    fadeAnim->setStartValue(0.0);
    fadeAnim->setEndValue(1.0);
    fadeAnim->setEasingCurve(QEasingCurve::OutCubic);



    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}