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
    drag = nullptr;

    auto backGround = new QFrame(this);
    backGround->setStyleSheet("background-color: #535353; border-radius: 4px;");
    backGround->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    handle = new QLabel(backGround);
    handle->setText("<b>::</b>");
    handle->setFont(QFont("Arial", 13));
    handle->installEventFilter(this);
    handle->setContentsMargins(0, 0, 0, 1);

    lineEdit = new QLineEdit(backGround); // Правая часть — строка
    lineEdit->setFixedWidth(24);
    //lineEdit->setStyleSheet("background-color: #303030; border-radius: 4px;");


    changeButton = new QPushButton("c", backGround);
    changeButton->setVisible(false);



    auto backGrounglayout = new QHBoxLayout(backGround);
    backGrounglayout->setContentsMargins(3, 0, 5, 0);
    backGrounglayout->setSpacing(5);
    backGrounglayout->addStretch();
    backGrounglayout->addWidget(handle, 0, Qt::AlignCenter);
    backGrounglayout->addWidget(lineEdit, 0, Qt::AlignCenter);
    backGrounglayout->addWidget(changeButton, 0, Qt::AlignCenter);
    backGrounglayout->addStretch();

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(5, 5, 0, 0);
    layout->addWidget(backGround);

    //animation
    lineEditAnimation = new QPropertyAnimation(lineEdit, "minimumWidth", this);
    lineEditAnimation->setDuration(150);
    lineEditAnimation->setEasingCurve(QEasingCurve::OutCubic); 

    connect(lineEdit, &QLineEdit::textChanged, this, [this]() {
        QFontMetrics fm(lineEdit->font());
        int textWidth = fm.horizontalAdvance(lineEdit->text()) + 15;

        lineEditAnimation->stop();

        lineEditAnimation->setStartValue(lineEdit->width());
        lineEditAnimation->setEndValue(textWidth);

        lineEditAnimation->start();

        this->updateGeometry();
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
            if (!(mouseEvent->buttons() & Qt::LeftButton)) //маска
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
                qobject_cast<ContainerPolynom*>(this->parentWidget())->animateLayoutUpdate();
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

    auto* effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);

    auto* anim = new QPropertyAnimation(effect, "opacity", this);
    anim->setDuration(duration);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);

    // по завершении анимации — скрыть виджет
    connect(anim, &QPropertyAnimation::finished, this, [this]() {
        this->hide();
        // Можно также удалить эффект, если он больше не нужен
        this->setGraphicsEffect(nullptr);
        this->parentWidget()->layout()->removeWidget(this);
        qobject_cast<ContainerPolynom*>(this->parentWidget())->animateLayoutUpdate();
        });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}