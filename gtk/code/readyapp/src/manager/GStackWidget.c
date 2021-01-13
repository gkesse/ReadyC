//===============================================
#include "GStackWidget.h"
#include "GMap.h"
//===============================================
GDECLARE_MAP(GStackWidget, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GStackWidget, GVOID_PTR, GVOID_PTR)
//===============================================
static void GStackWidget_Widget(GWidgetO* obj);
static void GStackWidget_AddWidget(GWidgetO* obj, GtkWidget* widget);
static void GStackWidget_SetCurrentIndex(GWidgetO* obj, int index);
static int GStackWidget_Count(GWidgetO* obj);
//===============================================
GWidgetO* GStackWidget_New() {
    GWidgetO* lParent = GWidget("widget");
    GStackWidgetO* lChild =(GStackWidgetO*)malloc(sizeof(GStackWidgetO));
    
    lChild->parent = lParent;
    lChild->count = 0;
    lChild->currentIndex = 0;
    lChild->widgetMap = GMap_New(GStackWidget, GVOID_PTR, GVOID_PTR)();
    
    lParent->child = lChild;
    
    GStackWidget_Widget(lParent);
    
    lParent->Delete = GStackWidget_Delete;
    lParent->AddWidget = GStackWidget_AddWidget;
    lParent->SetCurrentIndex = GStackWidget_SetCurrentIndex;
    lParent->Count = GStackWidget_Count;
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
static void GStackWidget_AddWidget(GWidgetO* obj, GtkWidget* widget) {
    GStackWidgetO* lChild = obj->child;
    GMapO(GStackWidget, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    gtk_box_pack_start(GTK_BOX(obj->widget), widget, 0, 0, 0);
    lWidgetMap->SetData(lWidgetMap,(void*)lChild->count, widget, 0);
    gtk_widget_hide(widget);
    if(lChild->count == lChild->currentIndex) {gtk_widget_show_all(widget);}
    lChild->count++;
}
//===============================================
static void GStackWidget_SetCurrentIndex(GWidgetO* obj, int index) {
    GStackWidgetO* lChild = obj->child;
    GMapO(GStackWidget, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    GtkWidget* lWidget = lWidgetMap->GetData(lWidgetMap,(void*)lChild->currentIndex, 0);
    gtk_widget_hide(lWidget);
    lChild->currentIndex = index;
    lWidget = lWidgetMap->GetData(lWidgetMap,(void*)lChild->currentIndex, 0);
    gtk_widget_show_all(lWidget);
}
//===============================================
static int GStackWidget_Count(GWidgetO* obj) {
    GStackWidgetO* lChild = obj->child;
    return lChild->count;
}
//===============================================
