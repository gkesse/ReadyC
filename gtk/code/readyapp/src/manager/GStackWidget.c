//===============================================
#include "GStackWidget.h"
#include "GMap.h"
//===============================================
GDECLARE_MAP(GStackWidget, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GStackWidget, GVOID_PTR, GVOID_PTR)
//===============================================
static void GStackWidget_Widget(GWidgetO* obj);
static void GStackWidget_AddPage(GWidgetO* obj, char* key, char* title, GtkWidget* widget, int isDefault);
static void GStackWidget_SetCurrentPage(GWidgetO* obj, char* key);
static char* GStackWidget_GetTitle(GWidgetO* obj, char* key);
static char* GStackWidget_GetDefaultKey(GWidgetO* obj);
static int GStackWidget_Count(GWidgetO* obj);
//===============================================
GWidgetO* GStackWidget_New() {
    GWidgetO* lParent = GWidget("widget");
    GStackWidgetO* lChild =(GStackWidgetO*)malloc(sizeof(GStackWidgetO));
    
    lChild->parent = lParent;
    lChild->count = 0;
    lChild->currentKeyFlag = 1;
    lChild->defaultKey = "";
    lChild->currentKey = "";
    lChild->widgetMap = GMap_New(GStackWidget, GVOID_PTR, GVOID_PTR)();
    lChild->titleMap = GMap_New(GStackWidget, GVOID_PTR, GVOID_PTR)();
    
    lParent->child = lChild;
        
    lParent->Delete = GStackWidget_Delete;
    lParent->AddPage = GStackWidget_AddPage;
    lParent->SetCurrentPage = GStackWidget_SetCurrentPage;
    lParent->GetTitle = GStackWidget_GetTitle;
    lParent->GetDefaultKey = GStackWidget_GetDefaultKey;
    lParent->Count = GStackWidget_Count;

    GStackWidget_Widget(lParent);
    return lParent;
}
//===============================================
void GStackWidget_Delete(GWidgetO* obj) {
    GWidget_Delete(obj);
}
//===============================================
// method
//===============================================
static void GStackWidget_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(0, 0);
    obj->widget = lWidget;
}
//===============================================
static void GStackWidget_AddPage(GWidgetO* obj, char* key, char* title, GtkWidget* widget, int isDefault) {
    GStackWidgetO* lChild = obj->child;
    GMapO(GStackWidget, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    GMapO(GStackWidget, GVOID_PTR, GVOID_PTR)* lTitleMap = lChild->titleMap;
    
    lWidgetMap->SetData(lWidgetMap, key, widget, lWidgetMap->EqualChar);
    lTitleMap->SetData(lTitleMap, key, title, lTitleMap->EqualChar);

    gtk_box_pack_start(GTK_BOX(obj->widget), widget, 0, 0, 0);
    gtk_widget_hide(widget);
    
    if(lChild->currentKeyFlag == 1) {lChild->defaultKey = key; lChild->currentKey = key; lChild->currentKeyFlag = 0;}
    
    if(isDefault == 1) {lChild->defaultKey = key;}
    lChild->count++;
}
//===============================================
static void GStackWidget_SetCurrentPage(GWidgetO* obj, char* key) {
    GStackWidgetO* lChild = obj->child;
    GMapO(GStackWidget, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    GtkWidget* lWidget = lWidgetMap->GetData(lWidgetMap, lChild->currentKey, lWidgetMap->EqualChar);
    gtk_widget_hide(lWidget);
    lChild->currentKey = key;
    lWidget = lWidgetMap->GetData(lWidgetMap, lChild->currentKey, lWidgetMap->EqualChar);
    gtk_widget_show_all(lWidget);
}
//===============================================
static char* GStackWidget_GetTitle(GWidgetO* obj, char* key) {
    GStackWidgetO* lChild = obj->child;
    GMapO(GStackWidget, GVOID_PTR, GVOID_PTR)* lTitleMap = lChild->titleMap;
    char* lTitle = lTitleMap->GetData(lTitleMap, key, lTitleMap->EqualChar);
    return lTitle;
}
//===============================================
static char* GStackWidget_GetDefaultKey(GWidgetO* obj) {
    GStackWidgetO* lChild = obj->child;
    return lChild->defaultKey;
}
//===============================================
static int GStackWidget_Count(GWidgetO* obj) {
    GStackWidgetO* lChild = obj->child;
    return lChild->count;
}
//===============================================
