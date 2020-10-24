//===============================================
#include "GInsertItem.h"
#include "GManager.h"
//===============================================
GInsertItem::GInsertItem(QWidget* parent) : GWidget(parent) {
    setObjectName("GInsertItem");

    m_label = new QLabel;
    m_label->setObjectName("label");
    m_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    m_checkFlag = false;

    m_check = new QPushButton(m_label);
    m_check->setObjectName("check");
    m_check->setIcon(GManager::Instance()->loadPicto(fa::check, "white"));
    m_check->move(5, 5);
    m_check->setVisible(m_checkFlag);
    m_widgetId[m_check] = "check";

    m_setting = new QPushButton(m_label);
    m_setting->setObjectName("setting");
    m_setting->setIcon(GManager::Instance()->loadPicto(fa::cog, "white"));
    m_setting->setVisible(false);
    m_widgetId[m_setting] = "setting";

    m_icon = new QPushButton(m_label);
    m_icon->setObjectName("icon");

    m_menu = new GMenu(this);
    m_menu->setObjectName("menu");
    m_menu->addAction("select", "Sélectionner/Désélectionner l'élément", GManager::Instance()->loadPicto(fa::check, "white"));
    m_menu->addAction("delete", "Supprimer l'élément", GManager::Instance()->loadPicto(fa::trash, "white"));

    m_index = -1;

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_label);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_check, SIGNAL(clicked()), this, SLOT(slotItemClick()));
    connect(m_setting, SIGNAL(clicked()), this, SLOT(slotItemClick()));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotContextMenu(QPoint)));
}
//===============================================
GInsertItem::~GInsertItem() {

}
//===============================================
void GInsertItem::setContent(QString text) {
    m_label->setText(text);
}
//===============================================
void GInsertItem::setContent(QString text, QIcon icon, int iconSize) {
    m_label->setText(text);
    m_label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    m_icon->setIcon(icon);
    m_icon->setIconSize(QSize(iconSize, iconSize));
    m_iconSize = iconSize;
}
//===============================================
void GInsertItem::setIndex(int index) {
    m_index = index;
}
//===============================================
void GInsertItem::slotItemClick() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetId[lWidget];
    if(lWidgetId == "check") {
        m_checkFlag = !m_checkFlag;
        m_check->setVisible(m_checkFlag);
    }
    else if(lWidgetId == "setting") {
        slotContextMenu(QPoint());
    }
}
//===============================================
void GInsertItem::slotContextMenu(QPoint pos) {
    sGPage* lPage = GManager::Instance()->getData()->page;
    QPoint lPos = QCursor::pos();
    QString lAction = m_menu->open(lPos);

    if(lAction == "select") {
        m_checkFlag = !m_checkFlag;
        m_check->setVisible(m_checkFlag);
        return;
    }

    lPage->menu_id = lAction;
    lPage->menu_index = m_index;
    emit emitItemClick();
}
//===============================================
void GInsertItem::resizeEvent(QResizeEvent* event) {
    int lLabelW = m_label->width();
    int lLabelH = m_label->height();
    int lIconX = (lLabelW - m_iconSize)/2;
    int lIconY = (lLabelH - m_iconSize)/2;

    m_setting->move(lLabelW - 20, 5);
    m_icon->move(lIconX, lIconY);
}
//===============================================
