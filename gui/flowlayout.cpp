#include "flowlayout.h"
#include "widgetpolynom.h" // если нужно

#include <QtWidgets>


FlowLayout::FlowLayout(QWidget* parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    QLayoutItem* item;
    while ((item = takeAt(0)) != nullptr) {
        delete item;
    }
}

void FlowLayout::addItem(QLayoutItem* item)
{
    itemList.append(item);
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem* FlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem* FlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    return nullptr;
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    for (auto item : itemList)
        size = size.expandedTo(item->minimumSize());
    const QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}

void FlowLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

int FlowLayout::doLayout(const QRect& rect, bool testOnly) const
{
    int x = rect.x();
    int y = rect.y();
    int lineHeight = 0;

    for (auto item : itemList) {
        QWidget* widget = item->widget();
        if (!widget) continue;

        int spaceX = horizontalSpacing();
        int spaceY = verticalSpacing();
        if (spaceX == -1) spaceX = widget->style()->layoutSpacing(
            QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        if (spaceY == -1) spaceY = widget->style()->layoutSpacing(
            QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);

        QSize itemSize = item->sizeHint();
        int nextX = x + itemSize.width() + spaceX;
        if (nextX - spaceX > rect.right() && lineHeight > 0) {
            x = rect.x();
            y = y + lineHeight + spaceY;
            nextX = x + itemSize.width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), itemSize));

        x = nextX;
        lineHeight = qMax(lineHeight, itemSize.height());
    }
    return y + lineHeight - rect.y();
}

int FlowLayout::horizontalSpacing() const
{
    return (m_hSpace >= 0) ? m_hSpace : 6;
}

int FlowLayout::verticalSpacing() const
{
    return (m_vSpace >= 0) ? m_vSpace : 6;
}

void FlowLayout::insertWidget(int index, QWidget* widget)
{
    QLayoutItem* item = new QWidgetItem(widget);
    itemList.insert(index, item);
}


