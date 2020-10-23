//===============================================
#ifndef _GInsertBox_
#define _GInsertBox_
//===============================================
#include "GWidget.h"
#include "GMenu.h"
//===============================================
class GInsertBox : public GWidget {
    Q_OBJECT
    
public:
    GInsertBox(QWidget* parent = 0);
    virtual ~GInsertBox();

public:
    void addItem(GWidget *widget);

public:
    void slotItemClick();
    void slotContextMenu(QPoint pos);

private:
    QVBoxLayout* m_mainLayout;
    QScrollArea* m_scrollArea;
    QFrame* m_scrollWidget;
    QVBoxLayout* m_scrollLayout;
    QMap<int, QWidget*> m_widgetId;
    int m_index;
    int m_count;
    GMenu* m_menu;
};
//===============================================
#endif
//===============================================
