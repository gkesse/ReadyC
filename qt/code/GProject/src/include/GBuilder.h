//===============================================
#ifndef _GBuilder_
#define _GBuilder_
//===============================================
#include "GWidget.h"
//===============================================
class GBuilder : public GWidget {
    Q_OBJECT
    
public:
    GBuilder(QWidget* parent = 0);
    virtual ~GBuilder();
    
private:
    QVBoxLayout* m_mainLayout;
    GWidget* m_widget;
};
//===============================================
#endif
//===============================================
