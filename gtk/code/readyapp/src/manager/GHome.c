//===============================================
#include "GHome.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GHome, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GHome, GVOID_PTR, GVOID_PTR)
//===============================================
static void GHome_Widget(GWidgetO* obj);
static void GHome_AddItem(GWidgetO* obj, char* key, char* text);
//===============================================
static void GHome_OnItemClick(GtkWidget* widget, gpointer params);
//===============================================
GWidgetO* GHome_New() {
    GWidgetO* lParent = GWidget("widget");
    GHomeO* lChild = (GHomeO*)malloc(sizeof(GHomeO));
    
    lChild->parent = lParent;
    lChild->widgetMap = GMap_New(GHome, GVOID_PTR, GVOID_PTR)();
    
    lParent->child = lChild;
    
    GHome_Widget(lParent);
    
    lParent->Delete = GHome_Delete;
    lParent->AddItem = GHome_AddItem;
    return lParent;
}
//===============================================
void GHome_Delete(GWidgetO* obj) {
    GHome_Delete(obj);
}
//===============================================
// method
//===============================================
static void GHome_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GWidgetO* lListBox = GWidget("listbox");
    lListBox->AddItem(lListBox, "home/login", "Connexion");
    lListBox->AddItem(lListBox, "home/sqlite", "SQLite");
    lListBox->AddItem(lListBox, "home/opencv", "OpenCV");
    lListBox->AddItem(lListBox, "home/debug", "Debug");
    
    gtk_box_pack_start(GTK_BOX(lWidget), lListBox->widget, 0, 0, 0);
}
//===============================================
static void GHome_AddItem(GWidgetO* obj, char* key, char* text) {
    GHomeO* lChild = obj->child;
    GMapO(GHome, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    GtkWidget* lButton = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lButton), text);
    gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);
    lWidgetMap->SetData(lWidgetMap, lButton, key, 0);
    g_signal_connect(G_OBJECT(lButton), "clicked", G_CALLBACK(GHome_OnItemClick), obj);
}
//===============================================
// callback
//===============================================
static void GHome_OnItemClick(GtkWidget* widget, gpointer params) {
    GWidgetO* lObj = (GWidgetO*)params;
    GHomeO* lChild = lObj->child;
    GMapO(GHome, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    char* lKey = (char*)lWidgetMap->GetData(lWidgetMap, widget, 0);
    GManager()->SetPage(lKey);
}
//===============================================
