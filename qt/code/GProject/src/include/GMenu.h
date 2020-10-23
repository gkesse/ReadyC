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
    void addAction(QString key, QString text);
    void addAction(QString key, QString text, QIcon icon);
    QString open(QPoint pos);

private:
    QMenu* m_menu;
    QMap<QAction*, QString> m_actionId;
};
//===============================================
#endif
//===============================================
