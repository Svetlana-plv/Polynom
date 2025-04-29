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
#include <Qpainter>
#include <Qmenu>
#include <Qstyle>
#include <QStyleFactory>


widgetPolynom::widgetPolynom(QWidget* parent) : QWidget(parent)
{
    drag = nullptr;

    auto backGround = new QFrame(this);
    backGround->setStyleSheet("background-color: #535353; border-radius: 4px;");
    //backGround->setFixedHeight(40);
    backGround->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    backGround->setContentsMargins(0, 0, 0, 0);


    handle = new QLabel(backGround);
    handle->setText("<b>::</b>");
    handle->setFont(QFont("Arial", 13));
    handle->installEventFilter(this);
    handle->setContentsMargins(0, 0, 0, 1);

    color = new QFrame(backGround);
    color->setFixedWidth(7);
    color->setFixedHeight(14);
    color->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    color->setStyleSheet("background-color: #2a2a2a; border-radius: 3px;");


    lineEdit = new QLineEdit(backGround);
    lineEdit->setFixedWidth(50);
    lineEdit->setReadOnly(true);
    lineEdit->installEventFilter(this);
    //lineEdit->setStyleSheet("background-color: #303030; border-radius: 4px;");


    changeButton = new QPushButton(backGround);
    changeButton->setIcon(QIcon(":/icons/edit2.png"));
    changeButton->setVisible(false);
    //changeButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    changeButton->setIconSize(QSize(16, 16));
    changeButton->setText("");
    changeButton->setStyleSheet("border: none;");
    changeButton->installEventFilter(this);

    auto lineLayout = new QHBoxLayout(lineEdit);
    lineLayout->setContentsMargins(0, 0, 0, 0);
    lineLayout->addStretch();
    lineLayout->addWidget(changeButton);


    auto backGrounglayout = new QHBoxLayout(backGround);
    backGrounglayout->setContentsMargins(3, 0, 5, 0);
    backGrounglayout->setSpacing(5);
    backGrounglayout->addWidget(color);
    backGrounglayout->addWidget(handle, 0, Qt::AlignCenter);
    backGrounglayout->addWidget(lineEdit, 0, Qt::AlignCenter);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(5, 5, 0, 0);
    layout->addWidget(backGround);

    //animation
    lineEditAnimation = new QPropertyAnimation(lineEdit, "minimumWidth", this);
    lineEditAnimation->setDuration(150);
    lineEditAnimation->setEasingCurve(QEasingCurve::OutCubic); 

    //adding
    connect(lineEdit, &QLineEdit::textChanged, this, [this]() {
        QFontMetrics fm(lineEdit->font());

        int extra = this->width() - lineEdit->width();
        int textWidth = fm.horizontalAdvance(lineEdit->text()) + 10;

        int target = extra + textWidth;

        if (this->maximumWidth() < target) {
            this->setMaximumWidth(target);
        }
        qDebug() << this->maximumWidth();

        lineEditAnimation->stop();
        lineEditAnimation->setStartValue(lineEdit->width());
        lineEditAnimation->setEndValue(textWidth);
        lineEditAnimation->start();

        this->updateGeometry();
        });

    connect(lineEdit, &QLineEdit::editingFinished, this, [this]() {
        lineEdit->setReadOnly(true);
    });

}



bool widgetPolynom::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == handle) {
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

                QPixmap transparentPixmap(pixmap.size());
                transparentPixmap.fill(Qt::transparent);
                
                QPainter painter(&transparentPixmap);
                painter.setOpacity(0.5); // Установить прозрачность 50%
                painter.drawPixmap(0, 0, pixmap);
                painter.end();
                
                drag->setPixmap(transparentPixmap);
                drag->setHotSpot(mouseEvent->pos());

                update();
                qobject_cast<ContainerPolynom*>(this->parentWidget())->animateLayoutUpdate();
                drag->exec(Qt::MoveAction | Qt::CopyAction);
            }
            else {
                widgetPolynom* tmp = new widgetPolynom();
                tmp->lineEdit->setText(this->lineEdit->text());
                tmp->color->setStyleSheet(this->color->styleSheet());
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

    else if (obj == lineEdit) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            lineEdit->setReadOnly(false);
            lineEdit->setFocus();
            lineEdit->selectAll();
            return true;
        }
        else if (event->type() == QEvent::Enter) {
            changeButton->setVisible(true);
            return true;
        }
        else if (event->type() == QEvent::Leave) {
            changeButton->setVisible(false);
            return true;
        }
    }

    else if (obj == changeButton) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMenu* menu = new QMenu(this);

            QAction* action1 = menu->addAction("Edit text");
            QAction* action2 = menu->addAction("Reset");
            QAction* action4 = menu->addAction("Delete");
            QAction* action3 = menu->addAction("Color");

            QMenu* colorMenu = new QMenu("Choose color", menu);
            QList<QPair<QString, QColor>> colors = {
                {"Red", QColor("#FF1744")},
                {"Green", QColor("#C6FF00")},
                {"Blue", QColor("#2979FF")},
                {"Yellow", QColor("#FFEA00")},
                {"Pink", QColor("#FFD1DC")}
            };

            for (auto& pair : colors) {
                QAction* colorAction = colorMenu->addAction(pair.first);
                colorAction->setData(pair.second);
            }

            connect(menu, &QMenu::hovered, this, [this, menu, action3, colorMenu](QAction* hoveredAction) {
                if (hoveredAction == action3) {
                    QRect actionRect = menu->actionGeometry(action3);
                    QPoint menuPos = menu->mapToGlobal(actionRect.topRight());
                    colorMenu->move(menuPos);
                    colorMenu->show();
                }
                else {
                    colorMenu->hide();
                }
                });

            connect(colorMenu, &QMenu::triggered, this, [this, colorMenu, menu](QAction* selectedColorAction) {
                if (selectedColorAction) {
                    QColor chosenColor = selectedColorAction->data().value<QColor>();
                    QString style = QString("background-color: %1; border-radius: 3px;").arg(chosenColor.name());
                    color->setStyleSheet(style);
                    colorMenu->close();
                    menu->close();
                }
                });

            QAction* selectedAction = menu->exec(changeButton->mapToGlobal(QPoint(0, changeButton->height())));

            if (selectedAction == action1) {
                lineEdit->setReadOnly(false);
                lineEdit->setFocus();
            }
            else if (selectedAction == action2) {
                lineEdit->setText("");
            }
            else if (selectedAction == action4) {
                this->fadeOutAndDelete(300);
            }

            colorMenu->hide();
            return true;
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

void widgetPolynom::fadeOutAndDelete(int duration)
{
    auto* effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);

    auto anim = new QPropertyAnimation(this, "maximumWidth");
    anim->setDuration((int)(duration / 2));
    anim->setStartValue(this->maximumWidth());
    anim->setEndValue(0);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    auto fadeanim = new QPropertyAnimation(effect, "opacity");
    fadeanim->setDuration(duration);
    fadeanim->setStartValue(1.0); 
    fadeanim->setEndValue(0.0);    


    connect(fadeanim, &QPropertyAnimation::finished, this, [this]() {
        if (this->parentWidget() && this->parentWidget()->layout()) {
            this->parentWidget()->layout()->removeWidget(this); 
        }
        this->hide();              
        this->setGraphicsEffect(nullptr); 
        this->deleteLater();       
        });

    fadeanim->start(QAbstractAnimation::DeleteWhenStopped);
    anim->start(QAbstractAnimation::DeleteWhenStopped); 
}

void widgetPolynom::enterEvent(QEnterEvent* event)
{
    QWidget::enterEvent(event);
    changeButton->setVisible(true);
}

void widgetPolynom::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    changeButton->setVisible(false);
}

QLineEdit* widgetPolynom::getLineEdit() const
{
    return lineEdit;
}

QFrame* widgetPolynom::getColor() const
{
    return color;
}