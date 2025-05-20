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

    loadAllFromDatabase();

    if (!ui->tabWidget->count()) addNewTab();

    ui->tabWidget->addTab(new QWidget(), "+");

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::addNewTab() {
    count++;
    tabWidget* tab = new tabWidget(this);
    tab->setMaximumSize(this->maximumSize());
    tab->setMinimumSize(this->minimumSize());


    // вставляем перед вкладкой "+"
    int plusIndex = ui->tabWidget->count() - 1;
    ui->tabWidget->insertTab(plusIndex, tab, QString("Profile %1").arg(count));
    ui->tabWidget->setCurrentIndex(plusIndex); // Переходим на новую вкладку
}


void MainWindow::saveAllToDataBase() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return;

    QSqlQuery clearPolys(db), clearProfiles(db);
    if (!clearPolys.exec("DELETE FROM polynomials")) {
        qDebug() << "error to clean polynomials:" << clearPolys.lastError().text();
        return;
    }
    if (!clearProfiles.exec("DELETE FROM profiles")) {
        qDebug() << "error to clean profiles:" << clearProfiles.lastError().text();
        return;
    }

    QSqlQuery insertProfile(db);
    insertProfile.prepare("INSERT INTO profiles (name, state) VALUES (?, ?)");

    QSqlQuery insertPoly(db);
    insertPoly.prepare("INSERT INTO polynomials (profile_id, expression, color, key) VALUES (?, ?, ?, ?)");

    for (int i = 0; i < ui->tabWidget->count() - 1; ++i) {
        QString profileName = ui->tabWidget->tabText(i);
        tabWidget* tab = qobject_cast<tabWidget*>(ui->tabWidget->widget(i));
        //QWidget* tab = ui->tabWidget->widget(i);

        insertProfile.addBindValue(profileName);
        if(tab->getCalculator())
            insertProfile.addBindValue(static_cast<int>(tab->getCalculator()->state));

        if (!insertProfile.exec()) {
            qDebug() << "error to add a profile:" << insertProfile.lastError().text();
            continue;
        }

        auto listL = static_cast<listLayout*>(tab->getCalculator()->getListLayout());
        auto mew = qobject_cast<listPolynom*>(listL->parentWidget());
        auto ccc = mew->container.get();

        int profileId = insertProfile.lastInsertId().toInt();

        QList<widgetPolynom*> polynoms = tab->getCalculator()->getListLayout()->getPolynomsFromLayout();
        for (widgetPolynom* w : polynoms) {
            insertPoly.addBindValue(profileId);
            insertPoly.addBindValue(QString::fromStdString(ccc->find(w->key)->value().get_str()));
            insertPoly.addBindValue(w->getColorHex());
            insertPoly.addBindValue(QString::fromStdString(w->key));

            if (!insertPoly.exec()) {
                qDebug() << "error to add a polynom:" << insertPoly.lastError().text();
            }
        }
    }
}


void MainWindow::loadAllFromDatabase() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return;

    QSqlQuery profileQuery("SELECT id, name, state FROM profiles");
    if (!profileQuery.exec()) {
        qDebug() << "error to query:" << profileQuery.lastError().text();
        return;
    }

    QSqlQuery polyQuery(db);

    while (profileQuery.next()) {
        int profileId = profileQuery.value(0).toInt();
        QString profileName = profileQuery.value(1).toString();
        int state = profileQuery.value(2).toInt();

        tabWidget* tab = new tabWidget(static_cast<ContainerType>(state), this);
        tab->setMaximumSize(this->maximumSize());
        tab->setMinimumSize(this->minimumSize());
        tab->getCalculator()->state = static_cast<ContainerType>(state);
        count++;
        //tab->setObjectName(profileName);
        
        polyQuery.prepare("SELECT expression, color, key FROM polynomials WHERE profile_id = ?");
        polyQuery.addBindValue(profileId);
        if (!polyQuery.exec()) {
            qDebug() << "error query: " << polyQuery.lastError().text();
            continue;
        }

        int i = 0;
        while (polyQuery.next()) {
            QString expr = polyQuery.value(0).toString();
            QColor color(polyQuery.value(1).toString());
            QString key = polyQuery.value(2).toString();

            auto listL = static_cast<listLayout*>(tab->getCalculator()->getListLayout());
            auto widgetP = new widgetPolynom(listL->parentWidget());
            
            widgetP->setColorHex(color);
            widgetP->key = key.toStdString();
            auto mew = qobject_cast<listPolynom*>(listL->parentWidget());
            auto ccc = mew->container.get();
            ccc->insert(key.toStdString(), expr.toStdString());
            listL->insertWidget(i, widgetP);
            
            widgetP->getLineEdit()->setText(key);

            i++;
        }

        ui->tabWidget->insertTab(ui->tabWidget->count()-1, tab, profileName);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    }
}

void MainWindow::onTabChanged(int index) {
    if (ui->tabWidget->tabText(index) == "+") {
        addNewTab();
    }
}


void MainWindow::closeEvent(QCloseEvent* event) {
    saveAllToDataBase();
    QMainWindow::closeEvent(event);
}