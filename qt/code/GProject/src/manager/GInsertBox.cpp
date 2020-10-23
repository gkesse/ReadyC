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

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_scrollArea);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
}
//===============================================
GInsertBox::~GInsertBox() {

}
//===============================================
void GInsertBox::addItem(QWidget* widget) {
    m_scrollLayout->addWidget(widget);
}
//===============================================
