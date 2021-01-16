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
    gtk_widget_set_name(lWidget, "GTitleBar");
    
    GtkWidget* lLogo = GManager()->Button2("logo_flat.png", 1, 20, 20, lApp->app_name, 5);

    GtkWidget* lTitle = gtk_label_new(0);
    lApp->title = lTitle;
    gtk_label_set_text(GTK_LABEL(lTitle), lApp->app_name);

    GtkWidget* lConnect = GManager()->Button("user", "Se Connecter", 5);
    gtk_widget_set_name(lConnect, "connect");
    gtk_widget_set_name(GTK_WIDGET(lConnect), "connect");
    GtkWidget* lFullscreen = GManager()->Button("eye", 0, 0);
    GtkWidget* lMinimize = GManager()->Button("windowminimize", 0, 0);
    GtkWidget* lMaximize = GManager()->Button("windowmaximize", 0, 0);
    GtkWidget* lClose = GManager()->Button("times", 0, 0);
    
    gtk_box_pack_start(GTK_BOX(lWidget), lLogo, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(5), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lTitle, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(5), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lConnect, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(10), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lFullscreen, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(10), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lMinimize, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(10), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lMaximize, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), GManager()->SpaceH(10), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lWidget), lClose, 0, 0, 0);    
}
//===============================================
