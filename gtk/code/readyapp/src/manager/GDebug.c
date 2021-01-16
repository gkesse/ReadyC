//===============================================
#include "GDebug.h"
#include "GManager.h"
//===============================================
static void GDebug_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GDebug_New() {
    GWidgetO* lParent = GWidget("widget");
    GDebugO* lChild = (GDebugO*)malloc(sizeof(GDebugO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GDebug_Delete;
    
    GDebug_Widget(lParent);
    return lParent;
}
//===============================================
void GDebug_Delete(GWidgetO* obj) {
    GDebug_Delete(obj);
}
//===============================================
// method
//===============================================
static void GDebug_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GtkWidget* lLabel = GManager()->Button(0, "GDebug", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLabel, 1, 1, 0);
}
//===============================================
