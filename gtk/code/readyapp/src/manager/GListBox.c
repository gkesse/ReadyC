//===============================================
#include "GListBox.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GListBox, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GListBox, GVOID_PTR, GVOID_PTR)
//===============================================
static void GListBox_Widget(GWidgetO* obj);
static void GListBox_AddItem(GWidgetO* obj, char* key, char* text, char* icon);
//===============================================
static void GListBox_OnItemClick(GtkWidget* widget, gpointer params);
//===============================================
GWidgetO* GListBox_New() {
    GWidgetO* lParent = GWidget("widget");
    GListBoxO* lChild = (GListBoxO*)malloc(sizeof(GListBoxO));
    
    lChild->parent = lParent;
    lChild->widgetMap = GMap_New(GListBox, GVOID_PTR, GVOID_PTR)();
    
    lParent->child = lChild;
    lParent->Delete = GListBox_Delete;
    lParent->AddItem = GListBox_AddItem;

    GListBox_Widget(lParent);
    return lParent;
}
//===============================================
void GListBox_Delete(GWidgetO* obj) {
    GListBox_Delete(obj);
}
//===============================================
// method
//===============================================
static void GListBox_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(0, 0);
    obj->widget = lWidget;
    gtk_widget_set_name(lWidget, "GListBox");
}
//===============================================
static void GListBox_AddItem(GWidgetO* obj, char* key, char* text, char* icon) {
    GListBoxO* lChild = obj->child;
    GMapO(GListBox, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    GtkWidget* lItem = gtk_button_new();
    gtk_widget_set_name(lItem, "item");
    GtkWidget* lLayout = gtk_hbox_new(0, 0);
    gtk_widget_set_name(lLayout, "row");
    GtkWidget* lButton = GManager()->Button(icon, text, 5, 0);
    gtk_box_pack_start(GTK_BOX(lLayout), lButton, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lLayout), gtk_hbox_new(0, 0), 1, 1, 0);
    gtk_container_add(GTK_CONTAINER(lItem), lLayout);
    gtk_box_pack_start(GTK_BOX(obj->widget), lItem, 0, 0, 0);
    lWidgetMap->SetData(lWidgetMap, lItem, key, 0);
    g_signal_connect(G_OBJECT(lItem), "clicked", G_CALLBACK(GListBox_OnItemClick), obj);
}
//===============================================
static void GListBox_OnItemClick(GtkWidget* widget, gpointer params) {
    sGApp* lApp = GManager()->mgr->app;;
    GWidgetO* lObj = (GWidgetO*)params;
    GListBoxO* lChild = lObj->child;
    GMapO(GListBox, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    char* lWidgetId = lWidgetMap->GetData(lWidgetMap, widget, 0);
    lApp->widget_id = lWidgetId;
    lObj->EmitItemClick(lObj);
}
//===============================================
