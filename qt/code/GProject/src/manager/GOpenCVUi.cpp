//===============================================
#include "GOpenCVUi.h"
#include "GManager.h"
//===============================================
GOpenCVUi::GOpenCVUi(QWidget* parent) : GWidget(parent) {
    setObjectName("GOpenCVUi");

    QLabel* lLabel = new QLabel("OpenCV");
    lLabel->setAlignment(Qt::AlignCenter);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(lLabel);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
}
//===============================================
GOpenCVUi::~GOpenCVUi() {

}
//===============================================
