//===============================================
#ifndef _GImageView_
#define _GImageView_
//===============================================
#include "GWidget.h"
//===============================================
class GImageView : public GWidget {
    Q_OBJECT
    
public:
    GImageView(QWidget* parent = 0);
    virtual ~GImageView();

private:
    QHBoxLayout* m_mainLayout;
    QLabel* m_image;
};
//===============================================
#endif
//===============================================
