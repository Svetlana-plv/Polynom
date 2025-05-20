#include "listLayout.h"
#include "widgetpolynom.h"

#include <QtWidgets>

listLayout::listLayout(QWidget* parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(0, 0, 0, 0);
}

listLayout::~listLayout()
{
    QLayoutItem* item;
    while ((item = takeAt(0)) != nullptr) {
        delete item;
    }
}

void listLayout::addItem(QLayoutItem* item)
{
    itemList.append(item);
}

int listLayout::count() const
{
    return itemList.size();
}

QLayoutItem* listLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem* listLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    return nullptr;
}

QSize listLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

QSize listLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

QSize listLayout::calculateSize(SizeType type) const
{
    QSize totalSize;
    int totalHeight = 0;
    int maxWidth = 0;

    for (const QLayoutItem* item : itemList) {
        QSize itemSize = (type == MinimumSize) ? item->minimumSize() : item->sizeHint();
        totalHeight += itemSize.height();
        maxWidth = qMax(maxWidth, itemSize.width());
    }

    if (!itemList.isEmpty()) {
        totalHeight += verticalSpacing() * (itemList.size() - 1);
    }

    const QMargins margins = contentsMargins();
    totalSize.setWidth(maxWidth + margins.left() + margins.right());
    totalSize.setHeight(totalHeight + margins.top() + margins.bottom());
    return totalSize;
}

void listLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);

    int y = rect.top() + contentsMargins().top();
    int x = rect.left() + contentsMargins().left();
    int layoutWidth = rect.width() - contentsMargins().left() - contentsMargins().right();

    for (QLayoutItem* item : qAsConst(itemList)) {
        if (QWidget* widget = item->widget()) {
            QSize sizeHint = widget->sizeHint();
            int itemHeight = sizeHint.height();
            int itemWidth = qMin(sizeHint.width(), layoutWidth);

            QRect itemRect(x, y, itemWidth, itemHeight);
            item->setGeometry(itemRect);

            y += itemHeight + verticalSpacing();
        }
    }
}

int listLayout::horizontalSpacing() const
{
    return (m_hSpace >= 0) ? m_hSpace : 2;
}

int listLayout::verticalSpacing() const
{
    return (m_vSpace >= 0) ? m_vSpace : 6;
}

void listLayout::insertWidget(int index, QWidget* widget)
{
    QLayoutItem* item = new QWidgetItem(widget);
    itemList.insert(index, item);
    update();
}


QList<widgetPolynom*> listLayout::getPolynomsFromLayout() {
    QList<widgetPolynom*> result;

    for (int i = 0; i < layout()->count(); ++i) {
        QLayoutItem* item = layout()->itemAt(i);
        if (!item) continue;

        QWidget* widget = item->widget();
        if (!widget) continue;

        widgetPolynom* poly = qobject_cast<widgetPolynom*>(widget);
        if (poly) {
            result.append(poly);
        }
    }

    return result;
}


