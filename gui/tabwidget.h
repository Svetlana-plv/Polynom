#pragma once
#include "selectwidget.h"
#include "calculatorwidget.h"
#include "ordered_table_container.h"
#include "struct.h"

#include <QWidget>
#include <QStackedWidget>

class tabWidget : public QWidget {
    Q_OBJECT
public:
    ContainerType state = ContainerType::order_table; //def
    explicit tabWidget(QWidget* parent = nullptr, ContainerType state = ContainerType::order_table);

    CalculatorWidget* getCalculator();
    void switchCalculator();
private:
    SelectWidget* select;
    CalculatorWidget* calculator = 0;
    QStackedWidget* stackedWidget;
};