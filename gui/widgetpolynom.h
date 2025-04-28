#pragma once


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDrag>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPushButton>


class widgetPolynom : public QWidget {
    Q_OBJECT
private:
    QLabel* handle;
    QLineEdit* lineEdit;
    QPushButton* changeButton;
    QPoint startPos; // <= запомним начальное положение мышки
    QPropertyAnimation* lineEditAnimation;

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

public:
    QDrag* drag;
    void fadeOutAndHide(int duration = 300);
    explicit widgetPolynom(QWidget* parent = nullptr);
    QLineEdit* getLineEdit() const;
};