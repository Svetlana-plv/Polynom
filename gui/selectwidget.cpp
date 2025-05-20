#include "selectwidget.h"
#include "ui_selectwidget.h"

#include<QApplication>

SelectWidget::SelectWidget(QWidget* parent) : QWidget(parent), ui(new Ui::SelectWidget) {
	
	ui->setupUi(this);
	ui->pushButton_create->installEventFilter(this);
	ui->pushButton_address_hash->installEventFilter(this);
	ui->pushButton_avltree->installEventFilter(this);
	ui->pushButton_chain_hash->installEventFilter(this);
	ui->pushButton_ordered_table->installEventFilter(this);
	ui->pushButton_rbtree->installEventFilter(this);
	ui->pushButton_unorderd_table->installEventFilter(this);

	this->state = ContainerType::AVLtree;
}

SelectWidget::~SelectWidget() {
	delete ui;
}

bool SelectWidget::eventFilter(QObject* obj, QEvent* event) {
	if (obj == ui->pushButton_create) {
		//QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		switch (event->type())
		{
		case QEvent::MouseButtonPress:
			emit switchRequested(state);
			break;

		default:
			break;
		}
	}

	if (event->type() == QEvent::MouseButtonPress) {

		if (obj == ui->pushButton_address_hash) {state = ContainerType::address_hash;}
		if (obj == ui->pushButton_avltree) {state = ContainerType::AVLtree;}
		if (obj == ui->pushButton_chain_hash) {state = ContainerType::chain_hash;}
		if (obj == ui->pushButton_ordered_table) {state = ContainerType::order_table;}
		if (obj == ui->pushButton_rbtree) {state = ContainerType::RBtree;}
		if (obj == ui->pushButton_unorderd_table) {state = ContainerType::unorder_table;}
	}
	return QWidget::eventFilter(obj, event);
}