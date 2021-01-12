//===============================================
#include "GListBox.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GListBox, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GListBox, GVOID_PTR, GVOID_PTR)
//===============================================
static void GListBox_Widget(GWidgetO* obj);
static void GListBox_AddItem(GWidgetO* obj, char* key, char* text);
static void GListBox_End(GWidgetO* obj);
//===============================================
static void GListBox_OnItemClick(GtkWidget* widget, gpointer params);
//===============================================
GWidgetO* GListBox_New() {
    GWidgetO* lParent = GWidget("widget");
    GListBoxO* lChild = (GListBoxO*)malloc(sizeof(GListBoxO));
    
    lChild->parent = lParent;
    lChild->widgetMap = GMap_New(GListBox, GVOID_PTR, GVOID_PTR)();
    
    lParent->child = lChild;
    
    GListBox_Widget(lParent);
    
    lParent->Delete = GListBox_Delete;
    lParent->AddItem = GListBox_AddItem;
    lParent->End = GListBox_End;
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
}
//===============================================
static void GListBox_AddItem(GWidgetO* obj, char* key, char* text) {
    GListBoxO* lChild = obj->child;
    GMapO(GListBox, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    GtkWidget* lButton = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lButton), text);
    gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);
    lWidgetMap->SetData(lWidgetMap, lButton, key, 0);
    g_signal_connect(G_OBJECT(lButton), "clicked", G_CALLBACK(GListBox_OnItemClick), obj);
}
//===============================================
static void GListBox_End(GWidgetO* obj) {
    printf("GListBox_End\n");
    gtk_box_pack_start(GTK_BOX(obj->widget), gtk_vbox_new(0, 0), 1, 1, 0);
}
//===============================================
// callback
//===============================================
static void GListBox_OnItemClick(GtkWidget* widget, gpointer params) {
    GWidgetO* lObj = (GWidgetO*)params;
    GListBoxO* lChild = lObj->child;
    GMapO(GListBox, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    char* lKey = (char*)lWidgetMap->GetData(lWidgetMap, widget, 0);
    GManager()->SetPage(lKey);
}
//===============================================
