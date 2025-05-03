#pragma once

#include<QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SelectWidget; }
QT_END_NAMESPACE


class SelectWidget : public QWidget {
    Q_OBJECT

public:
    explicit SelectWidget(QWidget* parent = nullptr);
    ~SelectWidget();
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
private:
    Ui::SelectWidget* ui;

signals:
    void switchRequested();
};