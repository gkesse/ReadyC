//===============================================
#include "GMenu.h"
#include "GManager.h"
//===============================================
GMenu::GMenu(QWidget *parent) : QMenu(parent) {
    setObjectName("GMenu");
    m_menu = new QMenu(this);
    m_menu->setObjectName("menu");
}
//===============================================
GMenu::~GMenu() {
    
}
//===============================================
void GMenu::addAction(QString key, QString text) {
    QAction* lAction = m_menu->addAction(text);
    m_actionId[lAction] = key;
}
//===============================================
void GMenu::addAction(QString key, QString text, QIcon icon) {
    QAction* lAction = m_menu->addAction(icon, text);
    m_actionId[lAction] = key;
}
//===============================================
QString GMenu::open(QPoint pos) {
    QAction* lAction = m_menu->exec(pos);
    QString lActionId = m_actionId[lAction];
    return lActionId;
}
//===============================================
