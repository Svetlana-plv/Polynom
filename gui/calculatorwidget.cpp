#include "calculatorwidget.h"
#include "ui_calculatorwidget.h"

#include <QStyleFactory>
#include <QApplication>


CalculatorWidget::CalculatorWidget(QWidget* parent) : QWidget(parent), ui(new Ui::CalculatorWidget) {

    ui->setupUi(this);

    ui->pushButton_0->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_1->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_4->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_5->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_6->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_7->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_8->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_9->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_dot->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_x->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_y->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_z->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_plus->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_minus->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_multiply->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_up->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_clear->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_delete->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_right_bracket->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_left_bracket->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_red->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_blue->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_green->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_yellow->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_pink->setFocusPolicy(Qt::NoFocus);

    auto* container = new ContainerPolynom();
    auto* containerList = new listPolynom();
    ui->scrollArea->setWidget(container);
    ui->scrollArea_2->setWidget(containerList);

    this->setStyle(QStyleFactory::create("Fusion")); 
    this->setPalette(QApplication::palette());

}

CalculatorWidget::~CalculatorWidget() {
    delete ui;
}

void CalculatorWidget::on_pushButton_1_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "1"); }
void CalculatorWidget::on_pushButton_2_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "2"); }
void CalculatorWidget::on_pushButton_3_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "3"); }
void CalculatorWidget::on_pushButton_4_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "4"); }
void CalculatorWidget::on_pushButton_5_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "5"); }
void CalculatorWidget::on_pushButton_6_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "6"); }
void CalculatorWidget::on_pushButton_7_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "7"); }
void CalculatorWidget::on_pushButton_8_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "8"); }
void CalculatorWidget::on_pushButton_9_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "9"); }
void CalculatorWidget::on_pushButton_0_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "0"); }
void CalculatorWidget::on_pushButton_x_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "x"); }
void CalculatorWidget::on_pushButton_y_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "y"); }
void CalculatorWidget::on_pushButton_z_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "z"); }
void CalculatorWidget::on_pushButton_dot_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "."); }
void CalculatorWidget::on_pushButton_plus_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + " + "); }
void CalculatorWidget::on_pushButton_minus_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + " - "); }
//void CalculatorWidget::on_pushButton_minus_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + " * "); }
void CalculatorWidget::on_pushButton_up_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "^"); }
void CalculatorWidget::on_pushButton_left_bracket_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + "("); }
void CalculatorWidget::on_pushButton_right_bracket_clicked() { if (polynom) polynom->getLineEdit()->setText(polynom->getLineEdit()->text() + ")"); }
void CalculatorWidget::on_pushButton_delete_clicked() { if (polynom) { polynom->fadeOutAndDelete(150); QApplication::focusWidget()->clearFocus(); } }
void CalculatorWidget::on_pushButton_clear_clicked() { if (polynom) polynom->getLineEdit()->setText(""); }
void CalculatorWidget::on_pushButton_red_clicked() { if (polynom) polynom->setRedColor(); }
void CalculatorWidget::on_pushButton_green_clicked() { if (polynom) polynom->setGreenColor(); }
void CalculatorWidget::on_pushButton_blue_clicked() { if (polynom) polynom->setBlueColor(); }
void CalculatorWidget::on_pushButton_yellow_clicked() { if (polynom) polynom->setYellowColor(); }
void CalculatorWidget::on_pushButton_pink_clicked() { if (polynom) polynom->setPinkColor(); }


void CalculatorWidget::onPolynomRequestConnect(widgetPolynom* sender) {
    polynom = sender;
}

void CalculatorWidget::onPolynomUnrequestConnect() {
    polynom = nullptr;
    qDebug() << "unset polynom";
}

void CalculatorWidget::on_pushButton_clicked()
{
    auto flow = static_cast<FlowLayout*>(ui->scrollArea->widget()->layout());
    auto widgetP = new widgetPolynom();

    connect(widgetP, &widgetPolynom::requestConnect, this, &CalculatorWidget::onPolynomRequestConnect);
    connect(widgetP, &widgetPolynom::unrequestConnect, this, &CalculatorWidget::onPolynomUnrequestConnect);

    addWidgetAnimation(widgetP, flow);
    widgetP->getLineEdit()->setFocus();
}

void CalculatorWidget::addWidgetAnimation(QWidget* widget, FlowLayout* flow)
{
    auto widgetP = qobject_cast<widgetPolynom*>(widget);
    if (!widgetP) return;

    //int max = widgetP->maximumWidth();

    if (!flow) return;
    flow->addWidget(widgetP);


    auto anim = new QPropertyAnimation(widgetP, "maximumWidth", this);
    anim->setDuration(1000);
    anim->setStartValue(0);
    anim->setEndValue(400);
    anim->setEasingCurve(QEasingCurve::OutCubic); // Пружинистый эффект

    auto* effect = new QGraphicsOpacityEffect(widgetP);
    widgetP->setGraphicsEffect(effect);
    QPropertyAnimation* fadeAnim = new QPropertyAnimation(effect, "opacity");
    fadeAnim->setDuration(300);
    fadeAnim->setStartValue(0.0);
    fadeAnim->setEndValue(1.0);
    fadeAnim->setEasingCurve(QEasingCurve::OutCubic);



    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
