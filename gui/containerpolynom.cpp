#include "ContainerPolynom.h"
#include <QApplication>
#include <QWidget>
#include <iostream>
#include <QPainter>
#include <QTimer>
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
        event->acceptProposedAction(); 
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

        QByteArray ba = event->mimeData()->data("application/x-polynom-widget");
        QJsonDocument doc = QJsonDocument::fromJson(ba);

        widgetPolynom* w = new widgetPolynom();
        if (!doc.isNull() && doc.isObject()) {
            QJsonObject obj = doc.object();

            std::string key = obj["key"].toString().toStdString();
            std::string val = obj["value"].toString().toStdString();
            QString col = obj["color"].toString();
            bool setKeyAndValue = obj["bool"].toBool();

            
            w->key = key;
            w->value = val;
            w->getColor()->setStyleSheet(col);
            w->setKeyAndValue = setKeyAndValue;

            w->getLineEdit()->setText(QString::fromStdString(key));

        }

        if (!w) return;
       
        w->setParent(this);
        insertAnimated(w, insertIndex);  // Вставляем в новое место
        w->show();

        event->acceptProposedAction();

        animateLayoutUpdate();
        insertIndex = -1;  // Сбрасываем
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

void ContainerPolynom::animateLayoutUpdate()
{
    auto flow = static_cast<FlowLayout*>(layout());
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

void ContainerPolynom::insertAnimated(widgetPolynom* widget, int index)
{
    auto flow = static_cast<FlowLayout*>(layout());
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


polynomContainer* ContainerPolynom::getPolynomContainer() {
    return container.get();
}