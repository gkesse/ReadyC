//===============================================
#include "GLogin.h"
#include "GManager.h"
//===============================================
static void GLogin_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GLogin_New() {
    GWidgetO* lParent = GWidget("widget");
    GLoginO* lChild = (GLoginO*)malloc(sizeof(GLoginO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GLogin_Delete;
    
    GLogin_Widget(lParent);
    return lParent;
}
//===============================================
void GLogin_Delete(GWidgetO* obj) {
    GLogin_Delete(obj);
}
//===============================================
// method
//===============================================
static void GLogin_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GtkWidget* lLabel = GManager()->Button(0, "GLogin", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLabel, 1, 1, 0);
}
//===============================================
