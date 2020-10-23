//===============================================
#include "GWindow.h"
#include "GManager.h"
//===============================================
GWindow::GWindow(QWidget* parent) : GWidget(parent) {
    setObjectName("GWindow");
    sGQt* lQt = GManager::Instance()->getData()->qt;

    m_addressBar = GWidget::Create("addressbar");

    lQt->page_map = new QStackedWidget;

    addPage("home", GWidget::Create("home"));
    addPage("home/opencv", GWidget::Create("opencv"));
    addPage("home/builder", GWidget::Create("builder"), 1);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_addressBar);
    m_mainLayout->addWidget(lQt->page_map);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
    setWindowTitle(lQt->title);
    setWindowIcon(GManager::Instance()->loadPicto(lQt->icon, lQt->icon_color));
    resize(lQt->width, lQt->height);
}
//===============================================
GWindow::~GWindow() {

}
//===============================================
void GWindow::addPage(QString key, QWidget* widget, int index) {
    sGQt* lQt = GManager::Instance()->getData()->qt;
    lQt->page_id[key] = lQt->page_map->count();
    lQt->page_map->addWidget(widget);
    if(index == 1) {
        GManager::Instance()->setCurrentPage(key);
    }
}
//===============================================
