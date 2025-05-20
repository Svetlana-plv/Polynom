#pragma once
#include <QWidget>
#include <QFrame>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "listlayout.h"
#include "polynom_container.h"

class listPolynom : public QWidget {
    Q_OBJECT
public:
    explicit listPolynom(QWidget* parent = nullptr);
    void setContainer(std::unique_ptr<polynomContainer> newContainer);
    void animateLayoutUpdate();
    void insertAnimated(widgetPolynom* widget, int index);
    polynomContainer* getPolynomContainer();
    std::unique_ptr<polynomContainer> container;
protected:

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private:
    int insertIndex = -1;
};