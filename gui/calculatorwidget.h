#pragma once

#include "flowlayout.h"
#include "widgetpolynom.h"
#include "ContainerPolynom.h"
#include "listpolynom.h"
#include "struct.h"

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <Qlabel>

QT_BEGIN_NAMESPACE
namespace Ui { class CalculatorWidget; }
QT_END_NAMESPACE

class CalculatorWidget : public QWidget {
    Q_OBJECT

public:
    std::unique_ptr<polynomContainer> createContainer(ContainerType type);
    explicit CalculatorWidget(ContainerType state = ContainerType::order_table, QWidget* parent = nullptr);
    ~CalculatorWidget();
    void addWidgetAnimation(QWidget* widget, FlowLayout* flow);
    void repack(ContainerType state);
    ContainerType state = ContainerType::order_table;

    listLayout* getListLayout();
    CalculatorWidget* getCalculatorWidget();
private:
    listPolynom* containerList;
    ContainerPolynom* container;
    Ui::CalculatorWidget* ui;
    widgetPolynom* polynom = nullptr;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_dot_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_y_clicked();
    void on_pushButton_z_clicked();
    void on_pushButton_left_bracket_clicked();
    void on_pushButton_right_bracket_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_up_clicked();
    void on_pushButton_red_clicked();
    void on_pushButton_green_clicked();
    void on_pushButton_blue_clicked();
    void on_pushButton_yellow_clicked();
    void on_pushButton_pink_clicked();
    void onPolynomRequestConnect(widgetPolynom* sender);
    void onPolynomUnrequestConnect();
    void on_pushButton_calculate_clicked();
    void on_pushButton_select_clicked();
signals:
    void switchSelect(ContainerType state);
};