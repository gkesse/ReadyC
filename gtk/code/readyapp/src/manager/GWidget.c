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
#include "GLogin.h"
#include "GSQLiteGtk.h"
#include "GOpenCVGtk.h"
#include "GDebug.h"
//===============================================
#include "GList.h"
#include "GManager.h"
//===============================================
GDECLARE_LIST(GWidget, GVOID_PTR)
GDEFINE_LIST(GWidget, GVOID_PTR)
//===============================================
static void GWidget_SetContent(GWidgetO* obj, char* text);
static void GWidget_AddPage(GWidgetO* obj, char* key, char* title, GtkWidget* widget, int isDefault);
static void GWidget_SetCurrentPage(GWidgetO* obj, char* key);
static char* GWidget_GetTitle(GWidgetO* obj, char* key);
static char* GWidget_GetDefaultKey(GWidgetO* obj);
static int GWidget_Count(GWidgetO* obj);
static void GWidget_AddItem(GWidgetO* obj, char* key, char* text, char* icon);
static void GWidget_AddItemClick(GWidgetO* obj, GWidgetO* obs);
static void GWidget_EmitItemClick(GWidgetO* obj);
static void GWidget_OnItemClickObs(GWidgetO* obj);
static void GWidget_OnItemClick(GtkWidget* widget, gpointer params);
//===============================================
GWidgetO* GWidget_New() {
    GWidgetO* lObj = (GWidgetO*)malloc(sizeof(GWidgetO));
    //
    lObj->child = 0;
    lObj->widget = gtk_vbox_new(0, 0);
    lObj->item_map = GList_New(GWidget, GVOID_PTR)();
    //
    lObj->Delete = GWidget_Delete;
    lObj->SetContent = GWidget_SetContent;
    lObj->AddPage = GWidget_AddPage;
    lObj->SetCurrentPage = GWidget_SetCurrentPage;
    lObj->GetTitle = GWidget_GetTitle;
    lObj->GetDefaultKey = GWidget_GetDefaultKey;
    lObj->Count = GWidget_Count;
    lObj->AddItem = GWidget_AddItem;
    lObj->AddItemClick = GWidget_AddItemClick;
    lObj->EmitItemClick = GWidget_EmitItemClick;
    lObj->OnItemClickObs = GWidget_OnItemClickObs;
    lObj->OnItemClick = GWidget_OnItemClick;
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
    if(!strcmp(key, "login")) {return GLogin_New();}
    if(!strcmp(key, "sqlite")) {return GSQLiteGtk_New();}
    if(!strcmp(key, "opencv")) {return GOpenCVGtk_New();}
    if(!strcmp(key, "debug")) {return GDebug_New();}
    // default
    return GWidget_New();
}
//===============================================
// method
//===============================================
static void GWidget_AddItemClick(GWidgetO* obj, GWidgetO* obs) {
    GListO(GWidget, GVOID_PTR)* lItemMap = obj->item_map;
    lItemMap->AddData(lItemMap, obs);
}
//===============================================
static void GWidget_EmitItemClick(GWidgetO* obj) {
    GListO(GWidget, GVOID_PTR)* lItemMap = obj->item_map;
    int lSize = lItemMap->Size(lItemMap);
    for(int i = 0; i < lSize; i++) {
        GWidgetO* lObj = lItemMap->GetData(lItemMap, i);
        lObj->OnItemClickObs(lObj);
    }
}
//===============================================
// interface
//===============================================
static void GWidget_SetContent(GWidgetO* obj, char* text) {}
static void GWidget_AddPage(GWidgetO* obj, char* key, char* title, GtkWidget* widget, int isDefault) {}
static void GWidget_SetCurrentPage(GWidgetO* obj, char* key) {}
static char* GWidget_GetTitle(GWidgetO* obj, char* key) {return "";}
static char* GWidget_GetDefaultKey(GWidgetO* obj) {return "";}
static int GWidget_Count(GWidgetO* obj) {return 0;}
static void GWidget_AddItem(GWidgetO* obj, char* key, char* text, char* icon) {}
static void GWidget_OnItemClickObs(GWidgetO* obj) {}
static void GWidget_OnItemClick(GtkWidget* widget, gpointer params) {}
//===============================================
