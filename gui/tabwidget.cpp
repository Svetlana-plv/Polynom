#include "tabwidget.h"


tabWidget::tabWidget(QWidget* parent) {

	stackedWidget = new QStackedWidget(this);

	select = new SelectWidget(this);

	stackedWidget->addWidget(select);

	connect(select, &SelectWidget::switchRequested, this, [=](ContainerType state) {
		if (!calculator) {
			calculator = new CalculatorWidget(state, this);
			calculator->state = select->state;
			stackedWidget->addWidget(calculator);
		}
		else {
			calculator->state = select->state;
		}
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

tabWidget::tabWidget(ContainerType state, QWidget* parent) {
	stackedWidget = new QStackedWidget(this);

	calculator = new CalculatorWidget(state, this);

	stackedWidget->addWidget(calculator);

	stackedWidget->setCurrentWidget(calculator);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(stackedWidget);
	setLayout(layout);
}

void tabWidget::switchCalculator() {
	stackedWidget->setCurrentWidget(calculator);
}