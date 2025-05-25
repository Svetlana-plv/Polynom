#include "calculatorwidget.h"
#include "ordered_table_container.h"
#include "unordered_table_container.h"
#include "ui_calculatorwidget.h"

#include <QStyleFactory>
#include <QApplication>


CalculatorWidget::CalculatorWidget(ContainerType state, QWidget* parent) : QWidget(parent), ui(new Ui::CalculatorWidget) {

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

    ui->pushButton_select->setFocusPolicy(Qt::NoFocus);

    container = new ContainerPolynom();

    containerList = new listPolynom();
    containerList->setContainer(createContainer(state));

    ui->scrollArea->setWidget(container);
    ui->scrollArea_2->setWidget(containerList);

    this->setStyle(QStyleFactory::create("Fusion")); 
    this->setPalette(QApplication::palette());

    connect(ui->lineEdit, &QLineEdit::textChanged, this, [=](const QString& text) {
        qobject_cast<listLayout*>(ui->scrollArea_2->widget()->layout())->updateVisibleWidgets(text);
        });

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
void CalculatorWidget::on_pushButton_select_clicked() { emit switchSelect(state); }



void CalculatorWidget::onPolynomRequestConnect(widgetPolynom* sender) {
    polynom = sender;
}

void CalculatorWidget::onPolynomUnrequestConnect() {
    polynom = nullptr;
}

void CalculatorWidget::on_pushButton_clicked()
{
    auto flow = static_cast<FlowLayout*>(ui->scrollArea->widget()->layout());
    auto widgetP = new widgetPolynom();
    widgetP->getLineEdit()->setReadOnly(false);

    connect(widgetP, &widgetPolynom::requestConnect, this, &CalculatorWidget::onPolynomRequestConnect);
    connect(widgetP, &widgetPolynom::unrequestConnect, this, &CalculatorWidget::onPolynomUnrequestConnect);

    addWidgetAnimation(widgetP, flow);
    widgetP->getLineEdit()->setFocus();
}

void CalculatorWidget::on_pushButton_calculate_clicked() {
    auto flow = static_cast<FlowLayout*>(ui->scrollArea->widget()->layout());
    auto ccontainer = qobject_cast<ContainerPolynom*>(ui->scrollArea->widget());
    auto ccc = ccontainer->container.get();

    auto result = new widgetPolynom();
    std::string str = "";

    connect(result, &widgetPolynom::requestConnect, this, &CalculatorWidget::onPolynomRequestConnect);
    connect(result, &widgetPolynom::unrequestConnect, this, &CalculatorWidget::onPolynomUnrequestConnect);

    for (int i = 0; i < flow->count(); ++i) {
        QLayoutItem* item = flow->itemAt(i);
        QWidget* widget = item->widget();
        if (widget) {
            widgetPolynom* poly = qobject_cast<widgetPolynom*>(widget);
            str = str + poly->value;

            poly->fadeOutAndDelete(150);
        }
    }


    result->value = str;
    Polynom resPol;
    try {

        Lexer l;
        ParserE p;
        polishConverter pC;
        RPNCalculator rpn;

        vector<token> tokens =  l.makeTokens(str);
        if (p.parserExp(tokens)) {
            tokens = pC.toPolish(tokens);
            resPol = rpn.evaluate(tokens);
        }
        else {
            throw std::string("meow");
        }
        result->value = resPol.get_str();
    }
    catch (...){
        QMessageBox::critical(this, "error", "");
    }

    result->key = result->value;
    result->setKeyAndValue = true;
    result->getLineEdit()->setText(QString::fromStdString(result->key));
    addWidgetAnimation(result, flow);
}

void CalculatorWidget::addWidgetAnimation(QWidget* widget, FlowLayout* flow)
{
    auto widgetP = qobject_cast<widgetPolynom*>(widget);
    if (!widgetP) return;

    int max = widgetP->maximumWidth();

    if (!flow) return;
    flow->addWidget(widgetP);


    auto anim = new QPropertyAnimation(widgetP, "maximumWidth", this);
    anim->setDuration(300);
    anim->setStartValue(0);
    anim->setEndValue(max);
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

listLayout* CalculatorWidget::getListLayout() {
    auto list = static_cast<listLayout*>(ui->scrollArea_2->widget()->layout());
    return list;
}

CalculatorWidget* CalculatorWidget::getCalculatorWidget() {
    return this;
}

std::unique_ptr<polynomContainer> CalculatorWidget::createContainer(ContainerType type) {
    switch (type) {
    case ContainerType::order_table:
        return std::make_unique<orderedTablecontainer>();
    case ContainerType::unorder_table:
        return std::make_unique<unorderedTablecontainer>();
    case ContainerType::AVLtree:
        //return std::make_unique<ListPolynomContainer>();
        break;
    default:
        throw std::runtime_error("Unknown container type");
    }
}

void CalculatorWidget::repack(ContainerType state) {
    if (this->state == state) return;
    this->state = state;

    auto newContainer = std::make_unique<listPolynom>();
    newContainer->setContainer(createContainer(this->state));

    auto oldCtr = containerList->container.get();
    auto newCtr = newContainer->container.get();
    
    for (auto it = oldCtr->begin(); !(it->operator==(*oldCtr->end())); ++(*it)) {
        std::string key = it->key();
        std::string value = it->value().get_str();
        newCtr->insert(key, Polynom(value));
    }

    delete containerList;
    containerList = newContainer.release();
    ui->scrollArea_2->setWidget(containerList);
    auto layout = containerList->findChild<listLayout*>();
    if (layout) {
        layout->setContainer(containerList->container.get());
        layout->updateVisibleWidgets();
    }
}
