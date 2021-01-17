//===============================================
#include "GSQLiteGtk.h"
#include "GManager.h"
//===============================================
static void GSQLiteGtk_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GSQLiteGtk_New() {
    GWidgetO* lParent = GWidget("widget");
    GSQLiteGtkO* lChild = (GSQLiteGtkO*)malloc(sizeof(GSQLiteGtkO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GSQLiteGtk_Delete;
    
    GSQLiteGtk_Widget(lParent);
    return lParent;
}
//===============================================
void GSQLiteGtk_Delete(GWidgetO* obj) {
    GSQLiteGtk_Delete(obj);
}
//===============================================
// method
//===============================================
static void GSQLiteGtk_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GtkWidget* lLabel = GManager()->Button(0, "GSQLiteGtk", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLabel, 1, 1, 0);
}
//===============================================
