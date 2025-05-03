#pragma once
#include "selectwidget.h"
#include "calculatorwidget.h"

#include <QWidget>
#include <QStackedWidget>

class tabWidget : public QWidget {
    Q_OBJECT
public:
    explicit tabWidget(QWidget* parent = nullptr);

private:
    SelectWidget* select;
    CalculatorWidget* calculator;
    QStackedWidget* stackedWidget;
};