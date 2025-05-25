#pragma once
#include <QWidget>
#include <QFrame>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "flowlayout.h"
#include "polynom_container.h"

class ContainerPolynom : public QWidget {
    Q_OBJECT
public:
    std::unique_ptr<polynomContainer> container;
    explicit ContainerPolynom(QWidget* parent = nullptr);
    void animateLayoutUpdate();
    void insertAnimated(widgetPolynom* widget, int index);
    polynomContainer* getPolynomContainer();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    //void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void leaveEvent(QEvent* event) override;

    void calculate();
private:
    int insertIndex = -1;

};
