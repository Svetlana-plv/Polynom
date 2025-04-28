#pragma once

#include "widgetpolynom.h"

#include <QRect>
#include <QLayout>
#include <QList>
#include <QWidgetItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

class FlowLayout : public QLayout
{
public:
    FlowLayout(QWidget* parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    ~FlowLayout();

    void addItem(QLayoutItem* item) override;
    int count() const override;
    QLayoutItem* itemAt(int index) const override;
    QLayoutItem* takeAt(int index) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect& rect) override;

    int horizontalSpacing() const;
    int verticalSpacing() const;
    void insertWidget(int index, QWidget* widget);

private:
    int doLayout(const QRect& rect, bool testOnly) const;
    QList<QLayoutItem*> itemList;
    int m_hSpace;
    int m_vSpace;
};
