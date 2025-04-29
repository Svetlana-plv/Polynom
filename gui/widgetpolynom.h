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
    QFrame* color;
    QPoint startPos; 
    QPropertyAnimation* lineEditAnimation;

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

public:
    QDrag* drag;
    void fadeOutAndHide(int duration = 300);
    explicit widgetPolynom(QWidget* parent = nullptr);
    QLineEdit* getLineEdit() const;
    QFrame* getColor() const;
    void fadeOutAndDelete(int duration);
};