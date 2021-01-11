//===============================================
#include "GImageView.h"
#include "GManager.h"
//===============================================
GImageView::GImageView(QWidget* parent) : GWidget(parent) {
    setObjectName("GImageView");

    m_image = new QLabel;
    m_image->setObjectName("image");
    m_image->setAlignment(Qt::AlignCenter);

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->addWidget(m_image);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(5);

    setLayout(m_mainLayout);
}
//===============================================
GImageView::~GImageView() {
    
}
//===============================================
