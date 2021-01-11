//===============================================
#include "GListBox.h"
#include "GManager.h"
//===============================================
GListBox::GListBox(QWidget* parent) : GWidget(parent) {
    setObjectName("GListBox");
    
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
GListBox::~GListBox() {
    
}
//===============================================
void GListBox::addItem(QString key, QString text) {
    QPushButton* lButton = new QPushButton;
    lButton->setObjectName("item");
    lButton->setText(text);
    lButton->setCursor(Qt::PointingHandCursor);
    m_scrollLayout->addWidget(lButton);
    m_widgetId[lButton] = key;
    connect(lButton, SIGNAL(clicked()), this, SLOT(slotItemClick()));
}
//===============================================
void GListBox::addItem(QString key, QString text, QIcon icon) {
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
void GListBox::addItem(QString key, QString text, QIcon icon, int width, int height) {
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
void GListBox::slotItemClick() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetId[lWidget];
    GManager::Instance()->setCurrentPage(lWidgetId);
    emit emitItemClick();
    qDebug() << lWidgetId;
}
//===============================================
