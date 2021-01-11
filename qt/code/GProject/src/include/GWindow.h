//===============================================
#ifndef _GWindow_
#define _GWindow_
//===============================================
#include "GWidget.h"
//===============================================
class GWindow : public GWidget {
    Q_OBJECT
    
public:
    GWindow(QWidget* parent = 0);
    virtual ~GWindow();
    
public:
    void addPage(QString key, QWidget* widget, int index = 0);

private:
    QVBoxLayout* m_mainLayout;
    GWidget* m_addressBar;
};
//===============================================
#endif
//===============================================
