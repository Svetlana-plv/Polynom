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
#include <QPainter>
#include <QMenu>
#include <QStyle>
#include <QStyleFactory>
#include <QCursor>
#include <QTimer>
#include <QRegularExpression>



widgetPolynom::widgetPolynom(QWidget* parent) : QWidget(parent)
{
    polynom = new Polynom();
    //polynom->reset();

    drag = nullptr;
    auto backGround = new QFrame(this);
    backGround->setStyleSheet("background-color: #2d2d2d; border-radius: 4px;");
    backGround->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    backGround->setContentsMargins(0, 0, 0, 0);


    handle = new QLabel(backGround);
    handle->setContentsMargins(0, -1, 0, 1);
    handle->setFixedHeight(18);
    handle->setText("<b>::</b>");
    handle->setFont(QFont("Arial", 13));
    handle->setAttribute(Qt::WA_Hover, true);
    handle->installEventFilter(this);
    handle->adjustSize();


    color = new QFrame(backGround);
    color->setContentsMargins(0, 0, 0, -1);
    color->setFixedWidth(7);
    color->setFixedHeight(16);
    color->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    color->setStyleSheet("background-color: #ececec; border-radius: 3px;");


    lineEdit = new QLineEdit(backGround);
    lineEdit->setTextMargins(0, 2, 0, 0); 
    lineEdit->setFixedWidth(50);
    lineEdit->setFont(QFont("Courier New", 12, QFont::Normal, false));
    lineEdit->setReadOnly(false);
    lineEdit->installEventFilter(this);
    //if(polynom->)
    //qDebug() << polynom->get_str();
    //lineEdit->setText(QString::fromStdString((polynom->get_str())));

    QFontMetrics fm(lineEdit->font());

    int extra = this->width() - lineEdit->width();
    int textWidth = fm.horizontalAdvance(lineEdit->text()) + 15;
    this->setMaximumWidth(extra + textWidth + 15);

    auto backGrounglayout = new QHBoxLayout(backGround);
    backGrounglayout->setContentsMargins(0, 0, 5, 0);
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

    //connect(lineEdit, &QLineEdit::hasFocus, this, [this]() {
    //    this->parent()->parent();
    //});

    //adding
    connect(lineEdit, &QLineEdit::textChanged, this, [this]() {
        QFontMetrics fm(lineEdit->font());

        int extra = this->width() - lineEdit->width();
        int textWidth = fm.horizontalAdvance(lineEdit->text()) + 15;
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

        if (event->type() == QEvent::Enter) {
            handle->setStyleSheet("background-color: rgba(236, 236, 236, 0.12); border-radius: 3px;");
            return true;  
        }

        else if (event->type() == QEvent::Leave) {
            handle->setStyleSheet("background-color: #2d2d2d; border-radius: 3px;");
        }

        else if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                startPos = mouseEvent->pos(); 
            }
            else if (mouseEvent->button() == Qt::RightButton) {
                QMenu* menu = new QMenu(this);
                
                menu->setStyleSheet(menuStyle);
                
                QAction* action1 = menu->addAction("Edit text");
                QAction* action2 = menu->addAction("Reset");
                QAction* action4 = menu->addAction("Delete");

                QMenu* colorMenu = menu->addMenu("Color");

                colorMenu->setStyleSheet(menuStyle);

                QList<QPair<QString, QColor>> colors = {
                    {"Red", QColor("#FF1744")},
                    {"Green", QColor("#C6FF00")},
                    {"Blue", QColor("#2979FF")},
                    {"Yellow", QColor("#FFEA00")},
                    {"Pink", QColor("#FFD1DC")}
                };

                for (auto& pair : colors) {
                    colorMenu->addAction(pair.first)->setData(pair.second);
                }

                connect(menu, &QMenu::triggered, this, [this, action1, action2, action4](QAction* act) {
                    if (act == action1) {
                        lineEdit->setReadOnly(false);
                        lineEdit->setFocus();
                    }
                    else if (act == action2) {
                        lineEdit->clear();
                    }
                    else if (act == action4) {
                        this->fadeOutAndDelete(300);
                    }
                    });

                connect(colorMenu, &QMenu::triggered, this, [this](QAction* act) {
                    QColor c = act->data().value<QColor>();
                    color->setStyleSheet(
                        QString("background-color: %1; border-radius: 3px;")
                        .arg(c.name())
                    );
                    });

                menu->exec(handle->mapToGlobal(QPoint(0, handle->height())));
                return true;
            }
        }
        
        else if (event->type() == QEvent::MouseMove) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);


            if (!(mouseEvent->buttons() & Qt::LeftButton)) //маска
                return false;

            if ((mouseEvent->pos() - startPos).manhattanLength() < QApplication::startDragDistance())
                return false;
            handle->setStyleSheet("background-color: #2d2d2d; border-radius: 3px;");
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
                
                drag->setDragCursor(QPixmap(":/icons/no-drop.png"), Qt::IgnoreAction);
                drag->setDragCursor(QPixmap(":/icons/grabbing.png"), Qt::MoveAction);
                drag->setPixmap(transparentPixmap);
                drag->setHotSpot(this->mapFromGlobal(handle->mapToGlobal(mouseEvent->pos())));

                update();
                qobject_cast<ContainerPolynom*>(this->parentWidget())->animateLayoutUpdate();
                

                drag->exec(Qt::MoveAction | Qt::CopyAction);
            }
            else {
                widgetPolynom* tmp = new widgetPolynom();
                tmp->lineEdit->setText(this->lineEdit->text());
                tmp->color->setStyleSheet(this->color->styleSheet());
                tmp->setMaximumWidth(this->maximumWidth());
                qDebug() << tmp->maximumWidth();
                QDrag* drag = new QDrag(tmp);
                QMimeData* mimeData = new QMimeData;

                mimeData->setData("application/x-polynom-widget", QByteArray::number(reinterpret_cast<quintptr>(tmp)));
                drag->setMimeData(mimeData);

                drag->setDragCursor(QPixmap(":/icons/no-drop.png"), Qt::IgnoreAction);
                drag->setDragCursor(QPixmap(":/icons/grabbing.png"), Qt::MoveAction);
                QPixmap pixmap(this->size());
                pixmap.fill(Qt::transparent);
                this->render(&pixmap);
                drag->setPixmap(pixmap);
                drag->setHotSpot(this->mapFromGlobal(handle->mapToGlobal(mouseEvent->pos())));


                drag->exec(Qt::MoveAction | Qt::CopyAction);
                update();
            }

            //QApplication::restoreOverrideCursor();
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
        else if (event->type() == QEvent::FocusIn) {
            qDebug() << "focus";
            emit requestConnect(this);
        }
        else if (event->type() == QEvent::FocusOut) {
            qDebug() << "unfocus";
            lineEdit->setReadOnly(true);
            polynom->reset();
            try
            {
                polynom->parse_string(lineEdit->text().toStdString());
            }
            catch (...)
            {
                QMessageBox::critical(nullptr, "error", "error");
                lineEdit->setText("");
            }
            lineEdit->setMaximumWidth(1000);
            emit unrequestConnect();
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


QLineEdit* widgetPolynom::getLineEdit() const
{
    return lineEdit;
}

QString widgetPolynom::getPolynomStr() const {
    return lineEdit->text();
}

void widgetPolynom::setPolynomStr(const QString& str) {
    lineEdit->setText(str);
    if (polynom) {
        polynom->reset();
        try {
            polynom->parse_string(str.toStdString());
        }
        catch (...) {
            QMessageBox::critical(nullptr, "error", "error");
        }
    }
}

QString widgetPolynom::getColorHex() const {
    QString style = color->styleSheet();
    QRegularExpression regex("#[0-9A-Fa-f]{6}");
    QRegularExpressionMatch match = regex.match(style);
    if (match.hasMatch()) {
        return match.captured(0);
    }
    return "#000000"; // fallback
}

void widgetPolynom::setColorHex(const QColor& hexColor) {
    if (color) {
        color->setStyleSheet(QString("background-color: %1; border-radius: 3px;").arg(hexColor.name(QColor::HexArgb)));
    }
}

QFrame* widgetPolynom::getColor() const
{
    return color;
}

void widgetPolynom::setRedColor() {
    color->setStyleSheet(QString("background-color: #FF1744; border-radius: 3px; "));
}

void widgetPolynom::setBlueColor() {
    color->setStyleSheet(QString("background-color: #2979FF; border-radius: 3px; "));
}

void widgetPolynom::setGreenColor() {
    color->setStyleSheet(QString("background-color: #C6FF00; border-radius: 3px; "));
}

void widgetPolynom::setYellowColor() {
    color->setStyleSheet(QString("background-color: #FFEA00; border-radius: 3px;"));
}

void widgetPolynom::setPinkColor() {
    color->setStyleSheet(QString("background-color: #FFD1DC; border-radius: 3px;"));
}