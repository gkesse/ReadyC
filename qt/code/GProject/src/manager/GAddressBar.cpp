//===============================================
#include "GAddressBar.h"
#include "GManager.h"
//===============================================
GAddressBar::GAddressBar(QWidget* parent) : GWidget(parent) {
    setObjectName("GAddressBar");
    
    m_scrollLayout = new QVBoxLayout;
    m_scrollLayout->setAlignment(Qt::AlignTop);
    m_scrollLayout->setMargin(0);
    m_scrollLayout->setSpacing(0);

    m_scrollWidget = new QFrame;
    m_scrollWidget->setLayout(m_scrollLayout);

    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidget(m_scrollWidget);
    m_scrollArea->setWidgetResizable(true);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_scrollArea);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
}
//===============================================
GAddressBar::~GAddressBar() {
    
}
//===============================================
void GAddressBar::addItem(QString key, QString text) {
    QPushButton* lButton = new QPushButton;
    lButton->setObjectName("item");
    lButton->setText(text);
    lButton->setCursor(Qt::PointingHandCursor);
    m_scrollLayout->addWidget(lButton);
    m_widgetId[lButton] = key;
    connect(lButton, SIGNAL(clicked()), this, SLOT(slotItemClick()));
}
//===============================================
void GAddressBar::addItem(QString key, QString text, QIcon icon) {
    QPushButton* lButton = new QPushButton;
    lButton->setObjectName("item");
    lButton->setText(text);
    lButton->setIcon(icon);
    lButton->setCursor(Qt::PointingHandCursor);
    m_scrollLayout->addWidget(lButton);
    m_widgetId[lButton] = key;
    connect(lButton, SIGNAL(clicked()), this, SLOT(slotItemClick()));
}
//===============================================
void GAddressBar::addItem(QString key, QString text, QIcon icon, int width, int height) {
    QPushButton* lButton = new QPushButton;
    lButton->setObjectName("item");
    lButton->setText(text);
    lButton->setIcon(icon);
    lButton->setIconSize(QSize(width, height));
    lButton->setCursor(Qt::PointingHandCursor);
    m_scrollLayout->addWidget(lButton);
    m_widgetId[lButton] = key;
    connect(lButton, SIGNAL(clicked()), this, SLOT(slotItemClick()));
}
//===============================================
void GAddressBar::slotItemClick() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetId[lWidget];
    GManager::Instance()->setCuurentPage(lWidgetId);
    emit emitItemClick();
}
//===============================================
