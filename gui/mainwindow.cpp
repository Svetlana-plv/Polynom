#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    addNewTab();

    ui->tabWidget->addTab(new QWidget(), "+");


    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::addNewTab() {
    static int count = 1;
    tabWidget* tab = new tabWidget(this);
    tab->setMaximumSize(this->maximumSize());
    tab->setMinimumSize(this->minimumSize());


    // вставляем перед вкладкой "+"
    int plusIndex = ui->tabWidget->count() - 1;
    ui->tabWidget->insertTab(plusIndex, tab, QString("Profile %1").arg(count));
    ui->tabWidget->setCurrentIndex(plusIndex); // Переходим на новую вкладку
    count++;
}

void MainWindow::onTabChanged(int index) {
    if (ui->tabWidget->tabText(index) == "+") {
        addNewTab();
    }
}


