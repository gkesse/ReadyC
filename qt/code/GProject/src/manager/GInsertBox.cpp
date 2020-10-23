//===============================================
#include "GInsertBox.h"
#include "GManager.h"
//===============================================
GInsertBox::GInsertBox(QWidget* parent) : GWidget(parent) {
    setObjectName("GInsertBox");

    m_scrollLayout = new QVBoxLayout;
    m_scrollLayout->setAlignment(Qt::AlignTop);
    m_scrollLayout->setMargin(0);
    m_scrollLayout->setSpacing(0);

    m_scrollWidget = new QFrame;
    m_scrollWidget->setLayout(m_scrollLayout);

    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidget(m_scrollWidget);
    m_scrollArea->setWidgetResizable(true);

    m_menu = new GMenu(this);
    m_menu->addAction("add", "Ajouter un élément", GManager::Instance()->loadPicto(fa::plus, "white"));

    m_index = 0;
    m_count = 0;

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_scrollArea);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotContextMenu(QPoint)));
}
//===============================================
GInsertBox::~GInsertBox() {

}
//===============================================
void GInsertBox::addItem(GWidget* widget) {
    m_scrollLayout->addWidget(widget);
    m_index++;
    m_widgetId[m_index] = widget;
    widget->setIndex(m_index);
    m_count++;
    connect(widget, SIGNAL(emitItemClick()), this, SLOT(slotItemClick()));
}
//===============================================
void GInsertBox::slotItemClick() {
    sGPage* lPage = GManager::Instance()->getData()->page;
    if(lPage->menu_id == "delete") {
        QWidget* lWidget = m_widgetId[lPage->menu_index];
        m_scrollLayout->removeWidget(lWidget);
        delete lWidget;
    }
}
//===============================================
void GInsertBox::slotContextMenu(QPoint pos) {
    QPoint lPos = QCursor::pos();
    QString lActionId = m_menu->open(lPos);
    qDebug() << lActionId;
}
//===============================================
