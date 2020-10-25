//===============================================
#ifndef _GInsertItem_
#define _GInsertItem_
//===============================================
#include "GWidget.h"
#include "GMenu.h"
//===============================================
class GInsertItem : public GWidget {
    Q_OBJECT
    
public:
    GInsertItem(QWidget* parent = 0);
    virtual ~GInsertItem();

public:
    void setContent(QString text);
    void setContent(QString text, QIcon icon, int iconSize);
    void setIndex(int index);

private:
    void setSelectText(int ok);

public slots:
    void slotItemClick();
    void slotContextMenu(QPoint pos);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    QVBoxLayout* m_mainLayout;
    QLabel* m_label;
    QPushButton* m_check;
    QPushButton* m_setting;
    QPushButton* m_icon;
    GMenu* m_menu;
    QMap<QAction*, QString> m_actionId;
    QMap<QWidget*, QString> m_widgetId;
    bool m_checkFlag;
    int m_iconSize;
    int m_index;
};
//===============================================
#endif
//===============================================
