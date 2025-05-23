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

	highlightSelectedButton();
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

		if (obj == ui->pushButton_address_hash) { state = ContainerType::address_hash; highlightSelectedButton(); }
		if (obj == ui->pushButton_avltree) { state = ContainerType::AVLtree;       highlightSelectedButton(); }
		if (obj == ui->pushButton_chain_hash) { state = ContainerType::chain_hash;    highlightSelectedButton(); }
		if (obj == ui->pushButton_ordered_table) { state = ContainerType::order_table;   highlightSelectedButton(); }
		if (obj == ui->pushButton_rbtree) { state = ContainerType::RBtree;        highlightSelectedButton(); }
		if (obj == ui->pushButton_unorderd_table) { state = ContainerType::unorder_table; highlightSelectedButton(); }
	}

	return QWidget::eventFilter(obj, event);
}

void SelectWidget::clearButtonStyles() {
	QString defaultStyle = ""; // Можно задать дефолтный стиль
	ui->pushButton_address_hash->setStyleSheet(defaultStyle);
	ui->pushButton_avltree->setStyleSheet(defaultStyle);
	ui->pushButton_chain_hash->setStyleSheet(defaultStyle);
	ui->pushButton_ordered_table->setStyleSheet(defaultStyle);
	ui->pushButton_rbtree->setStyleSheet(defaultStyle);
	ui->pushButton_unorderd_table->setStyleSheet(defaultStyle);
}

void SelectWidget::highlightSelectedButton() {
	clearButtonStyles();

	QString highlightStyle =
		"QPushButton {"
		"  background-color: rgba(0, 255, 0, 100);"
		"  border: 1px solid #00aa00;"
		"  border-radius: 6px;"
		"  padding: 6px;"
		"}"
		"QPushButton:hover {"
		"  background-color: rgba(0, 255, 0, 180);"
		"}"
		"QPushButton:pressed {"
		"  background-color: rgba(0, 200, 0, 255);"
		"}";

	switch (state) {
	case ContainerType::address_hash:
		ui->pushButton_address_hash->setStyleSheet(highlightStyle);
		break;
	case ContainerType::AVLtree:
		ui->pushButton_avltree->setStyleSheet(highlightStyle);
		break;
	case ContainerType::chain_hash:
		ui->pushButton_chain_hash->setStyleSheet(highlightStyle);
		break;
	case ContainerType::order_table:
		ui->pushButton_ordered_table->setStyleSheet(highlightStyle);
		break;
	case ContainerType::RBtree:
		ui->pushButton_rbtree->setStyleSheet(highlightStyle);
		break;
	case ContainerType::unorder_table:
		ui->pushButton_unorderd_table->setStyleSheet(highlightStyle);
		break;
	default:
		break;
	}
}

void SelectWidget::setState(ContainerType newState) {
	state = newState;
	highlightSelectedButton();
}