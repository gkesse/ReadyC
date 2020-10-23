//===============================================
#include "GInsertItem.h"
#include "GManager.h"
//===============================================
GInsertItem::GInsertItem(QWidget* parent) : GWidget(parent) {
    setObjectName("GInsertItem");

    m_label = new QLabel;
    m_label->setObjectName("label");
    m_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    m_check = new QCheckBox(m_label);
    m_check->setObjectName("check");
    m_check->move(5, 5);

    m_setting = new QPushButton(m_label);
    m_setting->setObjectName("setting");
    m_setting->setIcon(GManager::Instance()->loadPicto(fa::cog, "white"));

    m_icon = new QPushButton(m_label);
    m_icon->setObjectName("icon");

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_label);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);

    connect(m_check, SIGNAL(clicked(bool)), this, SLOT(slotCheckClick(bool)));
    connect(m_setting, SIGNAL(clicked()), this, SLOT(slotSettingClick()));
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
void GInsertItem::slotCheckClick(bool ok) {
    qDebug() << ok;
}
//===============================================
void GInsertItem::slotSettingClick() {

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
