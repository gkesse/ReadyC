//===============================================
#ifndef _GAddressList_
#define _GAddressList_
//===============================================
#include "GWidget.h"
//===============================================
class GAddressList : public GWidget {
    Q_OBJECT
    
public:
    GAddressList(QWidget* parent = 0);
    virtual ~GAddressList();

public:
    void setAddress(QString address);

public slots:
    void slotItemClick();

private:
    QHBoxLayout* m_mainLayout;
    QMap<QWidget*, QString> m_widgetId;
};
//===============================================
#endif
//===============================================
