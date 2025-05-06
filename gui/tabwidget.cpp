#include "tabwidget.h"

tabWidget::tabWidget(QWidget* parent) {

	stackedWidget = new QStackedWidget(this);

	calculator = new CalculatorWidget(this);
	select = new SelectWidget(this);

	stackedWidget->addWidget(calculator);

	stackedWidget->addWidget(select);

	connect(select, &SelectWidget::switchRequested, this, [=]() {
		stackedWidget->setCurrentWidget(calculator);
		});


	stackedWidget->setCurrentWidget(select);


	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(stackedWidget);
	setLayout(layout);
}

CalculatorWidget* tabWidget::getCalculator() {
	return calculator;
}

void tabWidget::switchCalculator() {
	stackedWidget->setCurrentWidget(calculator);
}