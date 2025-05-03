#include "selectwidget.h"
#include "ui_selectwidget.h"

#include<QApplication>

SelectWidget::SelectWidget(QWidget* parent) : QWidget(parent), ui(new Ui::SelectWidget) {
	ui->setupUi(this);
	ui->pushButton->installEventFilter(this);
}

SelectWidget::~SelectWidget() {
	delete ui;
}

bool SelectWidget::eventFilter(QObject* obj, QEvent* event) {
	if (obj == ui->pushButton) {
		//QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		switch (event->type())
		{
		case QEvent::MouseButtonPress:
			emit switchRequested();
			break;

		default:
			break;
		}
	}

	return QWidget::eventFilter(obj, event);
}