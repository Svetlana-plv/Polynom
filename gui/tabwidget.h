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
    std::unique_ptr<polynomContainer> container;

    explicit tabWidget(QWidget* parent = nullptr);
    explicit tabWidget(ContainerType state, QWidget* parent = nullptr);

    CalculatorWidget* getCalculator();
    void switchCalculator();
private:
    SelectWidget* select;
    CalculatorWidget* calculator = 0;
    QStackedWidget* stackedWidget;
};