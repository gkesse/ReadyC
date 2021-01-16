//===============================================
#include "GAddressBar.h"
#include "GManager.h"
//===============================================
static void GAddressBar_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GAddressBar_New() {
    GWidgetO* lParent = GWidget("widget");
    GAddressBarO* lChild = (GAddressBarO*)malloc(sizeof(GAddressBarO));
    
    lChild->parent = lParent;    
    lParent->child = lChild;
    
    GAddressBar_Widget(lParent);
    
    lParent->Delete = GAddressBar_Delete;
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
    GtkWidget* lWidget = gtk_hbox_new(0, 0);
    obj->widget = lWidget;
    gtk_widget_set_name(lWidget, "GAddressBar");

    GtkWidget* lIcon = GManager()->Button("home", 0, 0);
    
    GtkWidget* lEdit = gtk_entry_new();
    
    GtkWidget* lGoTo = GManager()->Button("paperplaneo", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lIcon, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(5), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lEdit, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(5), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lGoTo, 0, 0, 0);
}
//===============================================
