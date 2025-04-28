#include "listlayout.h"
#include "listpolynom.h"

#include <QApplication>
#include <QWidget>
#include <iostream>
#include <QPainter>

listPolynom::listPolynom(QWidget* parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setLayout(new listLayout(this));
}

void listPolynom::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-polynom-widget")) {
        event->acceptProposedAction();
    }
}

void listPolynom::dragMoveEvent(QDragMoveEvent* event)
{
    // Если перетаскиваемые данные в правильном формате, разрешаем перемещение
    if (event->mimeData()->hasFormat("application/x-polynom-widget")) {
        event->acceptProposedAction();

        QPoint pos = event->pos();
        insertIndex = -1;  // Сброс

        auto Llayout = static_cast<listLayout*>(layout());
        int count = Llayout->count();
        int minDistance = INT_MAX;

        for (int i = 0; i < count; ++i) {
            QWidget* widget = Llayout->itemAt(i)->widget();
            if (widget) {
                QRect geo = widget->geometry();
                int centerY = geo.center().y();
                int distance = qAbs(pos.y() - centerY);

                if (distance < minDistance) {
                    minDistance = distance;
                    insertIndex = i;
                }
            }
        }

        qDebug() << insertIndex;
        if (count == 0) {
            insertIndex = 0;
        }
        else if (insertIndex == -1) {
            insertIndex = count;
        }

        update();
    }
}

void listPolynom::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-polynom-widget")) {

        auto Llayout = static_cast<listLayout*>(layout());

        QByteArray ba = event->mimeData()->data("application/x-polynom-widget");
        widgetPolynom* w = reinterpret_cast<widgetPolynom*>(ba.toULongLong());

        if (!w) return;
        int count = Llayout->count();
         

        bool flag = false;
        for (int i = 0; i < count; ++i) {
            if (w->getLineEdit()->text() == qobject_cast<widgetPolynom*>(Llayout->itemAt(i)->widget())->getLineEdit()->text()) {
                flag = true;
                break;
            }
        }

        if (count == 0 || !flag) {
            Llayout->insertWidget(insertIndex, w);
            w->setParent(this);
            w->show();
            Llayout->invalidate();
        }
        update();

        event->acceptProposedAction();

        insertIndex = -1;  // Сбрасываем
    }
}

void listPolynom::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    if (insertIndex >= 0) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::blue, 2, Qt::DashLine));

        auto layout = static_cast<listLayout*>(this->layout());

        if (insertIndex < layout->count()) {
            QWidget* widget = layout->itemAt(insertIndex)->widget();
            if (widget) {
                QRect geo = widget->geometry();
                int y = geo.top();
                painter.drawLine(geo.left(), y, geo.right(), y);
            }
        }
        else if (layout->count() > 0) {
            QWidget* widget = layout->itemAt(layout->count() - 1)->widget();
            if (widget) {
                QRect geo = widget->geometry();
                int y = geo.bottom();
                painter.drawLine(geo.left(), y, geo.right(), y);
            }
        }
    }
}