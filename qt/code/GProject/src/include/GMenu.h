//===============================================
#ifndef _GMenu_
#define _GMenu_
//===============================================
#include "GWidget.h"
//===============================================
class GMenu : public QMenu {
    Q_OBJECT
    
public:
    GMenu(QWidget* parent = 0);
    virtual ~GMenu();

public:
    QString open(QPoint pos);
    void addAction(QString key, QString text);
    void addAction(QString key, QString text, QIcon icon);
    void addAction(QString key, QString text, QIcon icon, bool check);
    void setContent(QString text);

private:
    QMenu* m_menu;
    QAction* m_action;
    QMap<QAction*, QString> m_actionId;
};
//===============================================
#endif
//===============================================
