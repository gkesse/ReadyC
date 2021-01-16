//===============================================
#include "GSQLiteUi.h"
#include "GManager.h"
//===============================================
static void GSQLiteUi_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GSQLiteUi_New() {
    GWidgetO* lParent = GWidget("widget");
    GSQLiteUiO* lChild = (GSQLiteUiO*)malloc(sizeof(GSQLiteUiO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GSQLiteUi_Delete;
    
    GSQLiteUi_Widget(lParent);
    return lParent;
}
//===============================================
void GSQLiteUi_Delete(GWidgetO* obj) {
    GSQLiteUi_Delete(obj);
}
//===============================================
// method
//===============================================
static void GSQLiteUi_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GtkWidget* lLabel = GManager()->Button(0, "GSQLiteUi", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLabel, 1, 1, 0);
}
//===============================================
