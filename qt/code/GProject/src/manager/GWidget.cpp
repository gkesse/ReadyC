//===============================================
#include "GWidget.h"
// widget
#include "GListBox.h"
#include "GInsertBox.h"
#include "GInsertItem.h"
#include "GAddressBar.h"
#include "GAddressList.h"
// window
#include "GWindow.h"
// page
#include "GHome.h"
#include "GBuilder.h"
#include "GOpenCVUi.h"
//===============================================
GWidget::GWidget(QWidget* parent) : QFrame(parent) {
    setObjectName("GWidget");
}
//===============================================
GWidget::~GWidget() {
    
}
//===============================================
GWidget* GWidget::Create(QString key, QWidget* parent) {
    // listbox
    if(key == "listbox") return new GListBox(parent);
    if(key == "insertbox") return new GInsertBox(parent);
    if(key == "insertitem") return new GInsertItem(parent);
    if(key == "menu") return new GInsertItem(parent);
    if(key == "addresslist") return new GAddressList(parent);
    // window
    if(key == "window") return new GWindow(parent);
    // page
    if(key == "home") return new GHome(parent);
    if(key == "builder") return new GBuilder(parent);
    if(key == "opencv") return new GOpenCVUi(parent);
    // default
    return new GWidget(parent);
}
//===============================================
void GWidget::addItem(QString key, QString text) {}
void GWidget::addItem(QString key, QString text, QIcon icon) {}
void GWidget::addItem(QString key, QString text, QIcon icon, int width, int height) {}
void GWidget::addItem(GWidget *widget) {}
void GWidget::addAction(QString key, QString text) {}
void GWidget::addAction(QString key, QString text, QIcon icon) {}
void GWidget::addPage(QString key, QWidget* widget) {}
QString GWidget::open(QPoint pos) {return QString();}
void GWidget::setAddress(QString address) {}
void GWidget::setIndex(int index) {}
void GWidget::setContent(QString text) {}
void GWidget::setContent(QString text, QIcon icon, int iconSize) {}
//===============================================
void GWidget::slotRunClick() {}
void GWidget::slotItemClick() {}
void GWidget::slotCheckClick(bool ok) {}
void GWidget::slotSettingClick() {}
void GWidget::slotContextMenu(QPoint pos) {}
//===============================================
