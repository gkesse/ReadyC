//===============================================
#ifndef _GHome_
#define _GHome_
//===============================================
#include "GWidget.h"
//===============================================
class GHome : public GWidget {
    Q_OBJECT
    
public:
    GHome(QWidget* parent = 0);
    virtual ~GHome();
    
private:
    QVBoxLayout* m_mainLayout;
    GWidget* m_workspace;
};
//===============================================
#endif
//===============================================
