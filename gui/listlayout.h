#pragma once

#include "widgetpolynom.h"
#include "listpolynom.h"

#include <QRect>
#include <QLayout>
#include <QList>
#include <QWidgetItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

class listLayout : public QLayout
{
    Q_OBJECT
public:
    enum SizeType { MinimumSize, SizeHint };
    listLayout(QWidget* parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    ~listLayout();

    void addItem(QLayoutItem* item) override;
    int count() const override;
    QLayoutItem* itemAt(int index) const override;
    QLayoutItem* takeAt(int index) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    QSize calculateSize(SizeType type) const;
    void setGeometry(const QRect& rect) override;

    int horizontalSpacing() const;
    int verticalSpacing() const;
    void insertWidget(int index, QWidget* widget);
    QList<widgetPolynom*> getPolynomsFromLayout();
    
    void setContainer(polynomContainer* ctr);
    void updateVisibleWidgets(const QString& filter = "");
private:
    //int doLayout(const QRect& rect, bool testOnly) const;
    polynomContainer* container;
    QList<QLayoutItem*> itemList;
    int maxVisibleCount = 20;
    int m_hSpace;
    int m_vSpace;
};