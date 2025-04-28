#pragma once
#include <QWidget>
#include <QFrame>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "flowlayout.h"

class ContainerPolynom : public QWidget {
    Q_OBJECT
public:
    explicit ContainerPolynom(QWidget* parent = nullptr);
    void animateLayoutUpdate();
    void insertAnimated(widgetPolynom* widget, int index);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    //void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    int insertIndex = -1;
};
