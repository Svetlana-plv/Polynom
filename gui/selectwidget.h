#pragma once
#include "struct.h"

#include<QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SelectWidget; }
QT_END_NAMESPACE


class SelectWidget : public QWidget {
    Q_OBJECT

public:
    explicit SelectWidget(QWidget* parent = nullptr);
    ContainerType state;
    ~SelectWidget();
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
private:
    Ui::SelectWidget* ui;

signals:
    void switchRequested(ContainerType state);

private slots:
    //void on_pushButton_create_clicked();
    //void on_pushButton_ordered_table_clicked();
    //void on_pushButton_unorded_table_clicked();
    //void on_pushButton_avltree_clicked();
    //void on_pushButton_rbtree_clicked();
    //void on_pushButton_chain_hash_clicked();
    //void on_pushButton_address_hash_clicked();
};