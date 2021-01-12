//===============================================
#include "GTitleBar.h"
#include "GManager.h"
//===============================================
static void GTitleBar_Widget(GWidgetO* obj);
//===============================================
GWidgetO* GTitleBar_New() {
    GWidgetO* lParent = GWidget("widget");
    GTitleBarO* lChild = (GTitleBarO*)malloc(sizeof(GTitleBarO));
    
    lChild->parent = lParent;    
    lParent->child = lChild;
    
    GTitleBar_Widget(lParent);
    
    lParent->Delete = GTitleBar_Delete;
    return lParent;
}
//===============================================
void GTitleBar_Delete(GWidgetO* obj) {
    GWidget_Delete(obj);
}
//===============================================
// method
//===============================================
static void GTitleBar_Widget(GWidgetO* obj) {
    sGApp* lApp = GManager()->GetData()->app;
    GtkWidget* lWidget = gtk_hbox_new(0, 0);
    obj->widget = lWidget;
    
    GtkWidget* lLogo = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lLogo), "lLogo");
    
    GtkWidget* lAppName = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lAppName), "lAppName");
    
    GtkWidget* lTitle = gtk_label_new(0);
    lApp->title = lTitle;
    gtk_label_set_text(GTK_LABEL(lTitle), "lTitle");

    GtkWidget* lConnect = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lConnect), "lConnect");
    
    GtkWidget* lFullscreen = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lFullscreen), "lFullscreen");
    
    GtkWidget* lMinimize = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lMinimize), "lMinimize");
    
    GtkWidget* lMaximize = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lMaximize), "lMaximize");
    
    GtkWidget* lClose = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lClose), "lClose");
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLogo, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lAppName, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lTitle, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lFullscreen, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lMinimize, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lMaximize, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lClose, 0, 0, 0);    
}
//===============================================
