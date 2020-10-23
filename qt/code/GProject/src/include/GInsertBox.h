//===============================================
#ifndef _GInsertBox_
#define _GInsertBox_
//===============================================
#include "GWidget.h"
//===============================================
class GInsertBox : public GWidget {
    Q_OBJECT
    
public:
    GInsertBox(QWidget* parent = 0);
    virtual ~GInsertBox();

public:
    void addItem(QWidget* widget);

private:
    QVBoxLayout* m_mainLayout;
    QScrollArea* m_scrollArea;
    QFrame* m_scrollWidget;
    QVBoxLayout* m_scrollLayout;
    QMap<QWidget*, QString> m_widgetId;
};
//===============================================
#endif
//===============================================
