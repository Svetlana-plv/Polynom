#pragma once
#include <QWidget>
#include <QFrame>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "listlayout.h"

class listPolynom : public QWidget {
    Q_OBJECT
public:
    explicit listPolynom(QWidget* parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    int insertIndex = -1;
};