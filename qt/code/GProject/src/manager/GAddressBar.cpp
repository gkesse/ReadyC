//===============================================
#include "GAddressBar.h"
#include "GManager.h"
//===============================================
GAddressBar::GAddressBar(QWidget* parent) : GWidget(parent) {
    setObjectName("GAddressBar");
    sGQt* lQt = GManager::Instance()->getData()->qt;

    m_icon = new QPushButton;
    m_icon->setObjectName("icon");
    m_icon->setIcon(GManager::Instance()->loadPicto(fa::home, "white"));
    m_icon->setIconSize(QSize(25, 25));
    m_icon->setCursor(Qt::PointingHandCursor);

    m_address = new QLineEdit;
    m_address->setObjectName("address");

    m_goto = new QPushButton;
    m_goto->setObjectName("goto");
    m_goto->setIcon(GManager::Instance()->loadPicto(fa::paperplaneo, "white"));
    m_goto->setIconSize(QSize(25, 25));
    m_goto->setCursor(Qt::PointingHandCursor);

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->addWidget(m_icon);
    m_mainLayout->addWidget(m_address, 1);
    m_mainLayout->addWidget(m_goto);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(5);

    setLayout(m_mainLayout);

    lQt->address = m_address;

    connect(m_goto, SIGNAL(clicked()), this, SLOT(slotRunClick()));
}
//===============================================
GAddressBar::~GAddressBar() {
    
}
//===============================================
void GAddressBar::slotRunClick() {
    QString lAddress = m_address->text();
    GManager::Instance()->setCurrentPage(lAddress);
}
//===============================================
