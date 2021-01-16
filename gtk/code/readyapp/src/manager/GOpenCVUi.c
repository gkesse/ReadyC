//===============================================
#include "GOpenCVUi.h"
#include "GManager.h"
//===============================================
static void GOpenCVUi_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GOpenCVUi_New() {
    GWidgetO* lParent = GWidget("widget");
    GOpenCVUiO* lChild = (GOpenCVUiO*)malloc(sizeof(GOpenCVUiO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GOpenCVUi_Delete;
    
    GOpenCVUi_Widget(lParent);
    return lParent;
}
//===============================================
void GOpenCVUi_Delete(GWidgetO* obj) {
    GOpenCVUi_Delete(obj);
}
//===============================================
// method
//===============================================
static void GOpenCVUi_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GtkWidget* lLabel = GManager()->Button(0, "GOpenCVUi", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLabel, 1, 1, 0);
}
//===============================================
