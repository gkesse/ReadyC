//===============================================
#include "GWidget.h"
// widget
#include "GListBox.h"
// window
#include "GWindow.h"
// page
#include "GHome.h"
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
    // window
    if(key == "window") return new GWindow(parent);
    // page
    if(key == "home") return new GHome(parent);
    // default
    return new GWidget(parent);
}
//===============================================
void GWidget::addItem(QString key, QString text) {}
void GWidget::addItem(QString key, QString text, QIcon icon) {}
void GWidget::addItem(QString key, QString text, QIcon icon, int width, int height) {}
void GWidget::addPage(QString key, QWidget* widget) {}
//===============================================
void GWidget::slotItemClick() {}
//===============================================
