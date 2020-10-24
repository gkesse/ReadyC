//===============================================
#include "GBuilder.h"
#include "GManager.h"
//===============================================
GBuilder::GBuilder(QWidget* parent) : GWidget(parent) {
    setObjectName("GBuilder");
    sGQt* lQt = GManager::Instance()->getData()->qt;

    m_widget = GWidget::Create("insertbox");

    for(int i = 0; i < 10; i++) {
        QString lText = QString("Article %1").arg(i+1);
        GWidget* lItem = GWidget::Create("insertitem");
        lItem->setContent(lText, GManager::Instance()->loadPicto(fa::cameraretro, "white"), 40);
        m_widget->addItem(lItem);
    }

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_widget, 1);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(10);

    setLayout(m_mainLayout);

    setWindowTitle(lQt->title);
    setWindowIcon(GManager::Instance()->loadPicto(lQt->icon, lQt->icon_color));
    resize(lQt->width, lQt->height);

    connect(m_widget, SIGNAL(emitItemClick()), this, SLOT(slotItemClick()));
}
//===============================================
GBuilder::~GBuilder() {

}
//===============================================
void GBuilder::slotItemClick() {
    sGPage* lPage = GManager::Instance()->getData()->page;
    if(lPage->menu_id == "add") {
        int lIndex = m_widget->getIndex();
        QString lText = QString("Add %1").arg(lIndex+1);
        GWidget* lItem = GWidget::Create("insertitem");
        lItem->setContent(lText, GManager::Instance()->loadPicto(fa::cameraretro, "white"), 40);
        m_widget->addItem(lItem);
    }
    else if(lPage->menu_id ==  "insert") {
        int lIndex = m_widget->getIndex();
        QString lText = QString("Insert %1").arg(lIndex+1);
        GWidget* lItem = GWidget::Create("insertitem");
        lItem->setContent(lText, GManager::Instance()->loadPicto(fa::cameraretro, "white"), 40);
        m_widget->addItem(lItem, 0);
    }
}
//===============================================
