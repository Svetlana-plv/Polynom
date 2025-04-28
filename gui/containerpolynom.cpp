#include "ContainerPolynom.h"
#include <QApplication>
#include <QWidget>
#include <iostream>
#include <QPainter>
#include "widgetpolynom.h" // Подключаем виджет, который будем перетаскивать

ContainerPolynom::ContainerPolynom(QWidget* parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setLayout(new FlowLayout(this));
}

void ContainerPolynom::dragEnterEvent(QDragEnterEvent* event)
{
    // Проверяем, что перетаскиваемые данные имеют нужный формат
    if (event->mimeData()->hasFormat("application/x-polynom-widget")) {
        //event->setDropAction(Qt::MoveAction);
        event->acceptProposedAction();  // Разрешаем перетаскивание
    }

}

void ContainerPolynom::dragMoveEvent(QDragMoveEvent* event)
{
    // Если перетаскиваемые данные в правильном формате, разрешаем перемещение
    if (event->mimeData()->hasFormat("application/x-polynom-widget")) {
        event->acceptProposedAction();

        QPoint pos = event->pos();
        insertIndex = -1;  // Сброс

        auto flow = static_cast<FlowLayout*>(layout());

        int count = flow->count();
        int bestRowY = INT_MAX;
        int bestRowMinY = INT_MAX;

        // 1. Найти строку (по Y)
        for (int i = 0; i < count; ++i) {
            QWidget* widget = flow->itemAt(i)->widget();
            if (widget) {
                QRect geo = widget->geometry();
                int centerY = geo.center().y();
                if (qAbs(pos.y() - centerY) < qAbs(pos.y() - bestRowY)) {
                    bestRowY = centerY;
                    bestRowMinY = geo.top();
                }
            }
        }

        // 2. Найти позицию в этой строке (по X)
        for (int i = 0; i < count; ++i) {
            QWidget* widget = flow->itemAt(i)->widget();
            if (!widget) continue;
            
            QRect geo = widget->geometry().adjusted(-5, -5, 5, 5);
            if (geo.contains(pos)) {
                insertIndex = i;
                break;
    
            }
        }

        qDebug() << insertIndex;
        if (count == 0) {
            insertIndex = 0;
        }
        else if (insertIndex == -1)
            insertIndex = count;  // Если не нашли — вставить в конец
        update();  // Перерисовываем подсветку
    }
}

void ContainerPolynom::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-polynom-widget")) {

        auto flow = static_cast<FlowLayout*>(layout());

        QByteArray ba = event->mimeData()->data("application/x-polynom-widget");
        widgetPolynom* w = reinterpret_cast<widgetPolynom*>(ba.toULongLong());
        if (!w) return;
       
        w->setParent(this);
        flow->insertWidget(insertIndex, w);  // Вставляем в новое место
        w->show();

        flow->invalidate();

        event->acceptProposedAction();

        insertIndex = -1;  // Сбрасываем
        update();
    }
}

void ContainerPolynom::leaveEvent(QEvent* event)
{
    insertIndex = -1;
    update();           
}

void ContainerPolynom::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    if (insertIndex >= 0) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::blue, 2, Qt::DashLine));

        auto flow = static_cast<FlowLayout*>(layout());

        if (insertIndex < flow->count()) {
            QWidget* widget = flow->itemAt(insertIndex)->widget();
            if (widget) {
                QRect geo = widget->geometry();
                int x = geo.left();
                int yTop = geo.top();
                int yBottom = geo.bottom();
                painter.drawLine(x, yTop, x, yBottom);
            }
        }
        else if (flow->count() > 0) {
            QWidget* widget = flow->itemAt(flow->count() - 1)->widget();
            if (widget) {
                QRect geo = widget->geometry();
                int x = geo.right();
                int yTop = geo.top();
                int yBottom = geo.bottom();
                painter.drawLine(x, yTop, x, yBottom);
            }
        }
    }
}

