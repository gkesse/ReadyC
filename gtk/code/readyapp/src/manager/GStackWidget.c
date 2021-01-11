//===============================================
#include "GStackWidget.h"
//===============================================
static void GStackWidget_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GStackWidget_New() {
    GWidgetO* lParent = GWidget("widget");
    GStackWidgetO* lChild = (GStackWidgetO*)malloc(sizeof(GStackWidgetO));
    
    lChild->parent = lParent;    
    lParent->child = lChild;
    
    GStackWidget_Widget(lParent);
    
    lParent->Delete = GStackWidget_Delete;
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
    GtkWidget* lWidget = gtk_hbox_new(0, 0);
    obj->widget = lWidget;
        
    GtkWidget* lIcon = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lIcon), "lIcon");
    
    GtkWidget* lEdit = gtk_entry_new();
    
    GtkWidget* lGoTo = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lGoTo), "lGoTo");
    
    GtkWidget* lMainLayout = gtk_hbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lIcon, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lEdit, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lGoTo, 0, 0, 0);
    
    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
}
//===============================================
