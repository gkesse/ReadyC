//===============================================
#include "GStackWidget.h"
//===============================================
static void GStackWidget_Widget(GWidgetO* obj);
static void GStackWidget_AddWidget(GWidgetO* obj, GtkWidget* widget);
//===============================================
GWidgetO* GStackWidget_New() {
    GWidgetO* lParent = GWidget("widget");
    GStackWidgetO* lChild = (GStackWidgetO*)malloc(sizeof(GStackWidgetO));
    
    lChild->parent = lParent;
    lChild->count = 0;
    lChild->currentIndex = 0;
    lParent->child = lChild;
    
    GStackWidget_Widget(lParent);
    
    lParent->Delete = GStackWidget_Delete;
    lParent->AddWidget = GStackWidget_AddWidget;
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
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;
}
//===============================================
static void GStackWidget_AddWidget(GWidgetO* obj, GtkWidget* widget) {
    GStackWidgetO* lChild = (GStackWidgetO*)obj->child;
    gtk_box_pack_start(GTK_BOX(obj->widget), widget, 0, 0, 0);
    gtk_widget_hide_all(widget);
    if(lChild->count == lChild->currentIndex) {gtk_widget_show_all(widget);}
    lChild->count++;
}
//===============================================
