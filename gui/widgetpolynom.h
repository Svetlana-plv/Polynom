#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDrag>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include "polynom.h"
#include "polynom_container.h"
#include "struct.h"

class widgetPolynom : public QWidget {
    Q_OBJECT
private:
    QTimer* hoverTimer = nullptr;
    polynomContainer* container;
    QLabel* handle;
    QLineEdit* lineEdit;
    QFrame* color;
    QPoint startPos; 
    QPropertyAnimation* lineEditAnimation;
    void startDrag();
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

public:
    std::string key;
    Polynom* polynom;
    QTimer* debounceTimer = nullptr;
    QDrag* drag;
    void fadeOutAndHide(int duration = 300);
    explicit widgetPolynom(QWidget* parent = nullptr);
    const Polynom& getPolynom() const;
    //delete
    QLineEdit* getLineEdit() const;
    QFrame* getColor() const;
    void fadeOutAndDelete(int duration);

    QString menuStyle = R"(
    QMenu {
        background-color: #2d2d2d;      
        border: 1px solid #555555;    
        border-radius: 6px;             
        padding: 4px;                
    }
    QMenu::item {
        padding: 6px;     
        background-color: transparent;  
    }
    QMenu::item:selected {
        background-color: #444444;
    }
    QMenu::separator {
        height: 1px;
        background: #555555;
        margin: 5px 0;
    }
)";

    void setRedColor();
    void setGreenColor();
    void setBlueColor();
    void setYellowColor();
    void setPinkColor();

    QString getPolynomStr() const;
    void setPolynomStr(const QString& str);

    QString getColorHex() const;
    void setColorHex(const QColor& hexColor);

signals:
    void requestConnect(widgetPolynom* sender);
    void unrequestConnect();
};