#include "widgetpolynom.h"
#include "containerpolynom.h"

#include <iostream>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>


widgetPolynom::widgetPolynom(QWidget* parent) : QWidget(parent)
{
    auto backGround = new QFrame(this);
    drag = nullptr;
    handle = new QLabel(this);
    handle->setText("<b>::<b>");
    handle->setFont(QFont("Arial", 13));


    handle->installEventFilter(this);

    lineEdit = new QLineEdit(this); // Правая часть — строка
    lineEdit->setFixedWidth(24);
    lineEdit->setStyleSheet("background-color: #535353; border-radius: 4px;");

    auto backGrounglayout = new QHBoxLayout(backGround);
    backGrounglayout->setContentsMargins(0, 0, 0, 0);
    backGrounglayout->addWidget(handle);
    backGrounglayout->addWidget(lineEdit);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(backGround);

    connect(lineEdit, &QLineEdit::textChanged, this, [this]() {
        QFontMetrics fm(lineEdit->font());
        int textWidth = fm.horizontalAdvance(lineEdit->text());
        lineEdit->setFixedWidth(textWidth + 20);
        });



}

QLineEdit* widgetPolynom::getLineEdit() const
{
    return lineEdit;
}


bool widgetPolynom::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == handle) { // если событие пришло от "ручки"
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                startPos = mouseEvent->pos(); // запоминаем, где нажали мышь
            }
        }
        else if (event->type() == QEvent::MouseMove) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (!(mouseEvent->buttons() & Qt::LeftButton))
                return false;

            if ((mouseEvent->pos() - startPos).manhattanLength() < QApplication::startDragDistance())
                return false;
            
            if (qobject_cast<ContainerPolynom*>(this->parentWidget())) {
                this->fadeOutAndHide(90);
               

                QDrag* drag = new QDrag(this);
                QMimeData* mimeData = new QMimeData;

                mimeData->setData("application/x-polynom-widget", QByteArray::number(reinterpret_cast<quintptr>(this)));
                drag->setMimeData(mimeData);

                QPixmap pixmap(this->size());
                pixmap.fill(Qt::transparent);
                this->render(&pixmap);
                drag->setPixmap(pixmap);
                drag->setHotSpot(mouseEvent->pos());

                update();

                drag->exec(Qt::MoveAction | Qt::CopyAction);
            }
            else {
                widgetPolynom* tmp = new widgetPolynom();
                tmp->lineEdit->setText(this->lineEdit->text());
                QDrag* drag = new QDrag(tmp);
                QMimeData* mimeData = new QMimeData;

                mimeData->setData("application/x-polynom-widget", QByteArray::number(reinterpret_cast<quintptr>(tmp)));
                drag->setMimeData(mimeData);

                QPixmap pixmap(this->size());
                pixmap.fill(Qt::transparent);
                this->render(&pixmap);
                drag->setPixmap(pixmap);
                drag->setHotSpot(mouseEvent->pos());

                update();

                drag->exec(Qt::MoveAction | Qt::CopyAction);
            }

            return true; // событие обработано
        }
    }
    return QWidget::eventFilter(obj, event);
}

void widgetPolynom::fadeOutAndHide(int duration)
{
    // 1) Создаём эффект прозрачности
    auto* effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);

    // 2) Настраиваем анимацию свойства "opacity"
    auto* anim = new QPropertyAnimation(effect, "opacity", this);
    anim->setDuration(duration);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);

    // 3) По завершении анимации — скрыть виджет
    connect(anim, &QPropertyAnimation::finished, this, [this]() {
        this->hide();
        // Можно также удалить эффект, если он больше не нужен
        this->setGraphicsEffect(nullptr);
        this->parentWidget()->layout()->removeWidget(this);
        this->parentWidget()->layout()->invalidate();
        this->parentWidget()->layout()->update();
        });

    // 4) Запускаем анимацию
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}