//===============================================
#include "GAddressList.h"
#include "GManager.h"
//===============================================
GAddressList::GAddressList(QWidget* parent) : GWidget(parent) {
    setObjectName("GAddressList");

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setAlignment(Qt::AlignLeft);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(5);

    setLayout(m_mainLayout);
}
//===============================================
GAddressList::~GAddressList() {

}
//===============================================
void GAddressList::setAddress(QString address) {
    sGPage* lPage = GManager::Instance()->getData()->page;
    QPushButton* lHome = new QPushButton;
    lHome->setObjectName("home");
    lHome->setIcon(GManager::Instance()->loadPicto(fa::home, lPage->icon_color));
    lHome->setIconSize(QSize(lPage->icon_size, lPage->icon_size));
    lHome->setCursor(Qt::PointingHandCursor);
    m_mainLayout->addWidget(lHome);

    QStringList lAddressMap = address.split("/");
    QString lWidgetId = "";

    for(int i = 0; i < lAddressMap.size(); i++) {
        if(i != 0) {
            QPushButton* lChevron = new QPushButton;
            lChevron->setObjectName("sep");
            lChevron->setIcon(GManager::Instance()->loadPicto(fa::chevronright, lPage->icon_color));
            lChevron->setIconSize(QSize(lPage->icon_size, lPage->icon_size));
            m_mainLayout->addWidget(lChevron);
        }

        QString lAddress = lAddressMap[i];
        QPushButton* lButton = new QPushButton;
        lButton->setObjectName("item");
        lButton->setText(lAddress);
        lButton->setCursor(Qt::PointingHandCursor);
        m_mainLayout->addWidget(lButton);

        if(i != 0) lWidgetId += "/";
        lWidgetId += lAddress;

        m_widgetId[lButton] = lWidgetId;

        connect(lButton, SIGNAL(clicked()), this, SLOT(slotItemClick()));
    }
}
//===============================================
void GAddressList::slotItemClick() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetId[lWidget];
    GManager::Instance()->setCurrentPage(lWidgetId);
}
//===============================================
