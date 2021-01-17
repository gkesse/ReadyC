//===============================================
#include "GOpenCVGtk.h"
#include "GManager.h"
//===============================================
static void GOpenCVGtk_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GOpenCVGtk_New() {
    GWidgetO* lParent = GWidget("widget");
    GOpenCVGtkO* lChild = (GOpenCVGtkO*)malloc(sizeof(GOpenCVGtkO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GOpenCVGtk_Delete;
    
    GOpenCVGtk_Widget(lParent);
    return lParent;
}
//===============================================
void GOpenCVGtk_Delete(GWidgetO* obj) {
    GOpenCVGtk_Delete(obj);
}
//===============================================
// method
//===============================================
static void GOpenCVGtk_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GtkWidget* lLabel = GManager()->Button(0, "GOpenCVGtk", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLabel, 1, 1, 0);
}
//===============================================
