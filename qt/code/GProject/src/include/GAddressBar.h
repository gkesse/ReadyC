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
 
public:
    void addItem(QString key, QString text);
    void addItem(QString key, QString text, QIcon icon);
    void addItem(QString key, QString text, QIcon icon, int width, int height);

public slots:
    void slotItemClick();

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
