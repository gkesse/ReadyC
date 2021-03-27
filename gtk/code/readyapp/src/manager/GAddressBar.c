//===============================================
#include "GAddressBar.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GAddressBar, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GAddressBar, GVOID_PTR, GVOID_PTR)
//===============================================
static void GAddressBar_Widget(GWidgetO* obj);
static void GAddressBar_OnItemClick(GtkWidget* widget, gpointer params);
//===============================================
GWidgetO* GAddressBar_New() {
    GWidgetO* lParent = GWidget("widget");
    GAddressBarO* lChild = (GAddressBarO*)malloc(sizeof(GAddressBarO));
    
    lChild->parent = lParent;    
    lChild->widgetMap = GMap_New(GAddressBar, GVOID_PTR, GVOID_PTR)();

    lParent->child = lChild;
    lParent->Delete = GAddressBar_Delete;
    lParent->OnItemClick = GAddressBar_OnItemClick;
    
    GAddressBar_Widget(lParent);
    return lParent;
}
//===============================================
void GAddressBar_Delete(GWidgetO* obj) {
    GWidget_Delete(obj);
}
//===============================================
// method
//===============================================
static void GAddressBar_Widget(GWidgetO* obj) {
    sGApp* lApp = GManager()->mgr->app;
    GAddressBarO* lChild = obj->child;
    GtkWidget* lWidget = gtk_hbox_new(0, 0);
    obj->widget = lWidget;
    gtk_widget_set_name(lWidget, "GAddressBar");
    GMapO(GAddressBar, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;

    GtkWidget* lIcon = GManager()->Button("home", 0, 0, 0);
    lWidgetMap->SetData(lWidgetMap, (void*)lIcon, "icon", 0);
    GtkWidget* lEdit = gtk_entry_new();
    lApp->address_bar = lEdit;
    lWidgetMap->SetData(lWidgetMap, (void*)lEdit, "edit", 0);
    gtk_widget_set_name(lEdit, "edit");
    GtkWidget* lGoTo = GManager()->Button("paperplaneo", 0, 0, 0);
    lWidgetMap->SetData(lWidgetMap, (void*)lGoTo, "goto", 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lIcon, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(5), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lEdit, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(5), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lGoTo, 0, 0, 0);
    
    g_signal_connect(G_OBJECT(lIcon), "clicked", G_CALLBACK(obj->OnItemClick), obj);
    g_signal_connect(G_OBJECT(lEdit), "activate", G_CALLBACK(obj->OnItemClick), obj);
    g_signal_connect(G_OBJECT(lGoTo), "clicked", G_CALLBACK(obj->OnItemClick), obj);
}
//===============================================
static void GAddressBar_OnItemClick(GtkWidget* widget, gpointer params) {
    GWidgetO* lObj = (GWidgetO*)params;
    GAddressBarO* lChild = lObj->child;
    GMapO(GAddressBar, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    char* lPageId = (char*)lWidgetMap->GetData(lWidgetMap, (void*)widget, 0);
    printf("%s\n", lPageId);
    //GManager()->SetPage(lPageId);
}
//===============================================
