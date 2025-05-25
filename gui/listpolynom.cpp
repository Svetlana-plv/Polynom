#include "listlayout.h"
#include "listpolynom.h"

#include <QApplication>
#include <QWidget>
#include <iostream>
#include <QPainter>

listPolynom::listPolynom(QWidget* parent)
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

        QByteArray ba = event->mimeData()->data("application/x-polynom-widget");
        QJsonDocument doc = QJsonDocument::fromJson(ba);


        if (!doc.isNull() && doc.isObject()) {
            QJsonObject obj = doc.object();

            std::string key = obj["key"].toString().toStdString();
            std::string str = obj["value"].toString().toStdString();
            
            if (key == "" || container.get()->find(key)) {
                return;
            }

            //widgetPolynom* widget = new widgetPolynom();
           // widget->key = key;
            //widget->value = str;
            //widget->setKeyAndValue = false;

            container.get()->insert(key, Polynom(str));
            qobject_cast<listLayout*>(this->layout())->updateVisibleWidgets();
        }

        event->acceptProposedAction();

        animateLayoutUpdate();
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

void listPolynom::setContainer(std::unique_ptr<polynomContainer> newContainer) {
    container = std::move(newContainer);
    qobject_cast<listLayout*>(this->layout())->setContainer(container.get());
    qobject_cast<listLayout*>(this->layout())->update();
}

polynomContainer* listPolynom::getPolynomContainer() {
    return container.get();
}

void listPolynom::animateLayoutUpdate()
{
    auto flow = static_cast<listLayout*>(layout());
    if (!flow)
        return;

    QVector<QPropertyAnimation*> animations;


    QMap<QWidget*, QRect> oldGeometries;
    for (int i = 0; i < flow->count(); ++i) {
        QWidget* widget = flow->itemAt(i)->widget();
        if (widget) {
            oldGeometries[widget] = widget->geometry();
        }
    }

    flow->invalidate();
    flow->update();
    flow->activate();

    for (int i = 0; i < flow->count(); ++i) {
        QWidget* widget = flow->itemAt(i)->widget();
        if (widget && oldGeometries.contains(widget)) {
            QRect startRect = oldGeometries[widget];
            QRect endRect = widget->geometry();

            auto anim = new QPropertyAnimation(widget, "geometry", this);
            anim->setDuration(150);
            anim->setStartValue(startRect);
            anim->setEndValue(endRect);
            anim->setEasingCurve(QEasingCurve::OutCubic); // плавная кривая

            anim->start(QAbstractAnimation::DeleteWhenStopped);
            animations.append(anim);
        }
    }
}

void listPolynom::insertAnimated(widgetPolynom* widget, int index)
{
    auto flow = static_cast<listLayout*>(layout());
    if (!flow) return;

    flow->insertWidget(index, widget);

    int target = widget->maximumWidth();

    auto anim = new QPropertyAnimation(widget, "maximumWidth", this);
    anim->setDuration(600);
    anim->setStartValue(0);
    anim->setEndValue(target);
    anim->setEasingCurve(QEasingCurve::OutCubic); // Пружинистый эффект


    auto* effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);
    QPropertyAnimation* fadeAnim = new QPropertyAnimation(effect, "opacity");
    fadeAnim->setDuration(600);
    fadeAnim->setStartValue(0.0);
    fadeAnim->setEndValue(1.0);
    fadeAnim->setEasingCurve(QEasingCurve::OutCubic);


    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

}
