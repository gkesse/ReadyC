//===============================================
#ifndef _GOpenCVUi_
#define _GOpenCVUi_
//===============================================
#include "GWidget.h"
//===============================================
class GOpenCVUi : public GWidget {
    Q_OBJECT
    
public:
    GOpenCVUi(QWidget* parent = 0);
    virtual ~GOpenCVUi();
    
private:
    QVBoxLayout* m_mainLayout;
    GWidget* m_addressList;
    GWidget* m_workspace;
};
//===============================================
#endif
//===============================================
