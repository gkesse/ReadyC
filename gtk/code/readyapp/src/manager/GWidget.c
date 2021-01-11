//===============================================
// widget
#include "GWidget.h"
#include "GTitleBar.h"
#include "GAddressBar.h"
#include "GAddressKey.h"
#include "GStackWidget.h"
// page
#include "GWindow.h"
//===============================================
static void GWidget_SetContent(GWidgetO* obj);
//===============================================
GWidgetO* GWidget_New() {
    GWidgetO* lObj = (GWidgetO*)malloc(sizeof(GWidgetO));
    lObj->child = 0;
    lObj->widget = gtk_vbox_new(0, 0);
    lObj->Delete = GWidget_Delete;
    lObj->SetContent = GWidget_SetContent;
    return lObj;
}
//===============================================
void GWidget_Delete(GWidgetO* obj) {
    free(obj->child);
    free(obj);
}
//===============================================
GWidgetO* GWidget(const char* key) {
    // widget
    if(!strcmp(key, "widget")) {return GWidget_New();}
    if(!strcmp(key, "titlebar")) {return GTitleBar_New();}
    if(!strcmp(key, "addressbar")) {return GAddressBar_New();}
    if(!strcmp(key, "addresskey")) {return GAddressKey_New();}
    if(!strcmp(key, "stackwidget")) {return GStackWidget_New();}
    // page
    if(!strcmp(key, "window")) {return GWindow_New();}
    // default
    return GWidget_New();
}
//===============================================
// method
//===============================================
static void GWidget_SetContent(GWidgetO* obj) {}
//===============================================
