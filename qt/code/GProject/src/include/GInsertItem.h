//===============================================
#ifndef _GInsertItem_
#define _GInsertItem_
//===============================================
#include "GWidget.h"
//===============================================
class GInsertItem : public GWidget {
    Q_OBJECT
    
public:
    GInsertItem(QWidget* parent = 0);
    virtual ~GInsertItem();

public:
    void setContent(QString text);
    void setContent(QString text, QIcon icon, int iconSize);

public slots:
    void slotCheckClick(bool ok);
    void slotSettingClick();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    QVBoxLayout* m_mainLayout;
    QLabel* m_label;
    QCheckBox* m_check;
    QPushButton* m_setting;
    QPushButton* m_icon;
    int m_iconSize;
};
//===============================================
#endif
//===============================================
