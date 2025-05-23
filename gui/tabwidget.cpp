#include "tabwidget.h"


tabWidget::tabWidget(QWidget* parent, ContainerType state) {

	stackedWidget = new QStackedWidget(this);

	select = new SelectWidget(this);
	stackedWidget->addWidget(select);
	calculator = new CalculatorWidget(state, this);
	stackedWidget->addWidget(calculator);

	stackedWidget->setCurrentWidget(calculator);
	
	connect(calculator, &CalculatorWidget::switchSelect, this, [=](ContainerType state) {
		this->state = state;
		select->setState(state);
		stackedWidget->setCurrentWidget(select);
	});

	connect(select, &SelectWidget::switchRequested, this, [=](ContainerType state) {
		calculator->repack(state);
		stackedWidget->setCurrentWidget(calculator);
	});
	
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