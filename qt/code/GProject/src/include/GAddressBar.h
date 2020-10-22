//===============================================
#ifndef _GAddressBar_
#define _GAddressBar_
//===============================================
#include "GWidget.h"
//===============================================
class GAddressBar : public GWidget {
    Q_OBJECT
    
public:
    GAddressBar(QWidget* parent = 0);
    virtual ~GAddressBar();

public slots:
    void slotRunClick();

private:
    QHBoxLayout* m_mainLayout;
    QPushButton* m_icon;
    QLineEdit* m_address;
    QPushButton* m_goto;
};
//===============================================
#endif
//===============================================
