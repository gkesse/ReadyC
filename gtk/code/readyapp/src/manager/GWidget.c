//===============================================
// widget
#include "GWidget.h"
#include "GTitleBar.h"
#include "GAddressBar.h"
#include "GAddressKey.h"
#include "GStackWidget.h"
#include "GListBox.h"
// page
#include "GWindow.h"
#include "GHome.h"
//===============================================
static void GWidget_SetContent(GWidgetO* obj, char* text);
static void GWidget_AddWidget(GWidgetO* obj, GtkWidget* widget);
static void GWidget_SetCurrentIndex(GWidgetO* obj, int index);
static int GWidget_Count(GWidgetO* obj);
static void GWidget_AddItem(GWidgetO* obj, char* key, char* text);
static void GWidget_End(GWidgetO* obj);
//===============================================
GWidgetO* GWidget_New() {
    GWidgetO* lObj = (GWidgetO*)malloc(sizeof(GWidgetO));
    lObj->child = 0;
    lObj->widget = gtk_vbox_new(0, 0);
    lObj->Delete = GWidget_Delete;
    lObj->SetContent = GWidget_SetContent;
    lObj->AddWidget = GWidget_AddWidget;
    lObj->SetCurrentIndex = GWidget_SetCurrentIndex;
    lObj->Count = GWidget_Count;
    lObj->AddItem = GWidget_AddItem;
    lObj->End = GWidget_End;
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
    if(!strcmp(key, "listbox")) {return GListBox_New();}
    // page
    if(!strcmp(key, "window")) {return GWindow_New();}
    if(!strcmp(key, "home")) {return GHome_New();}
    // default
    return GWidget_New();
}
//===============================================
// method
//===============================================
static void GWidget_SetContent(GWidgetO* obj, char* text) {}
static void GWidget_AddWidget(GWidgetO* obj, GtkWidget* widget) {}
static void GWidget_SetCurrentIndex(GWidgetO* obj, int index) {}
static int GWidget_Count(GWidgetO* obj) {return 0;}
static void GWidget_AddItem(GWidgetO* obj, char* key, char* text) {}
static void GWidget_End(GWidgetO* obj) {}
//===============================================
