//===============================================
#include "GHome.h"
#include "GManager.h"
//===============================================
GHome::GHome(QWidget* parent) : GWidget(parent) {
    setObjectName("GHome");
    sGQt* lQt = GManager::Instance()->getData()->qt;
    sGPage* lPage = GManager::Instance()->getData()->page;

    m_addressList = GWidget::Create("addresslist");
    m_addressList->setAddress("home/opencv/show_image");

    m_workspace = GWidget::Create("listbox");
    m_workspace->addItem("home", "Accueil", GManager::Instance()->loadPicto(lPage->list_icon, lPage->icon_color), lPage->icon_size, lPage->icon_size);
    m_workspace->addItem("home/opencv", "OpenCV", GManager::Instance()->loadPicto(lPage->list_icon, lPage->icon_color), lPage->icon_size, lPage->icon_size);
    m_workspace->addItem("home/builder", "Builder", GManager::Instance()->loadPicto(lPage->list_icon, lPage->icon_color), lPage->icon_size, lPage->icon_size);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_addressList);
    m_mainLayout->addWidget(m_workspace, 1);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(10);

    setLayout(m_mainLayout);
    setWindowTitle(lQt->title);
    setWindowIcon(GManager::Instance()->loadPicto(lQt->icon, lQt->icon_color));
    resize(lQt->width, lQt->height);
}
//===============================================
GHome::~GHome() {

}
//===============================================
