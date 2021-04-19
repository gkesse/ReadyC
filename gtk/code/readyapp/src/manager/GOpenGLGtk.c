//===============================================
#include "GOpenGLGtk.h"
#include "GManager.h"
//===============================================
static void GOpenGLGtk_Widget(GWidgetO* obj);
static void GOpenGLGtk_OnRealize(GtkGLArea* glArea);
//===============================================
GWidgetO* GOpenGLGtk_New() {
    GWidgetO* lParent = GWidget("widget");
    GOpenGLGtkO* lChild = (GOpenGLGtkO*)malloc(sizeof(GOpenGLGtkO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GOpenGLGtk_Delete;
    
    GOpenGLGtk_Widget(lParent);
    return lParent;
}
//===============================================
void GOpenGLGtk_Delete(GWidgetO* obj) {
    GOpenGLGtk_Delete(obj);
}
//===============================================
// method
//===============================================
static void GOpenGLGtk_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;
    
    GtkWidget* lGlArea = gtk_gl_area_new();
    
    gtk_box_pack_start(GTK_BOX(lWidget), lGlArea, 1, 1, 0);
    
    g_signal_connect(G_OBJECT(lGlArea), "realize", G_CALLBACK(GOpenGLGtk_OnRealize), NULL);
}
//===============================================
static void GOpenGLGtk_OnRealize(GtkGLArea* glArea) {
	gtk_gl_area_make_current(glArea);

    if(gtk_gl_area_get_error(glArea) != NULL) {return;}
    
    printf("GOpenGLGtk_OnRealize............\n");
}
//===============================================
