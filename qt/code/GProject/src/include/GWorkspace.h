//===============================================
#ifndef _GListBox_
#define _GListBox_
//===============================================
#include "GWidget.h"
//===============================================
class GListBox : public GWidget {
    Q_OBJECT
    
public:
    GListBox(QWidget* parent = 0);
    virtual ~GListBox();
 
public:
    void addItem(QString text);
    void addItem(QString text, QIcon icon);
    void addItem(QString text, QIcon icon, int width, int height);

public slots:
    void slotItemClick();

private:
    QVBoxLayout* m_mainLayout;
    QScrollArea* m_scrollArea;
    QFrame* m_scrollWidget;
    QVBoxLayout* m_scrollLayout;
};
//===============================================
#endif
//===============================================
