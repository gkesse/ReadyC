//===============================================
#include "GWindow.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GWindow, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GWindow, GVOID_PTR, GVOID_PTR)
//===============================================
static void GWindow_Widget(GWidgetO* obj);
//===============================================
static void GWindow_OnDestroy(GtkWidget* obj, gpointer params);
static gboolean GWindow_OnDeleteEvent(GtkWidget* obj, GdkEvent* event, gpointer params);
//===============================================
GWidgetO* GWindow_New() {
    GWidgetO* lParent = GWidget("widget");
    GWindowO* lChild = (GWindowO*)malloc(sizeof(GWindowO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;
    lParent->Delete = GWindow_Delete;
    
    GWindow_Widget(lParent);
    return lParent;
}
//===============================================
void GWindow_Delete(GWidgetO* obj) {
    GWidget_Delete(obj);
}
//===============================================
// method
//===============================================
static void GWindow_Widget(GWidgetO* obj) {
    sGApp* lApp = GManager()->mgr->app;
    GtkWidget* lWidget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    obj->widget = lWidget;
    
    GWidgetO* lTitleBar = GWidget("titlebar");
    GWidgetO* lAddressBar = GWidget("addressbar");

    GWidgetO* lAddressKey = GWidget("addresskey");
    lApp->address_key = lAddressKey;

    GWidgetO* lWorkspace = GWidget("stackwidget");
    lApp->page_map = lWorkspace;
    gtk_widget_set_name(lWorkspace->widget, "workspace");
    
    GtkWidget* lMainLayout = gtk_vbox_new(0, 0);
    gtk_widget_set_name(lMainLayout, "GWindow");
    gtk_box_pack_start(GTK_BOX(lMainLayout), lTitleBar->widget, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), GManager()->SpaceV(10), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lAddressBar->widget, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), GManager()->SpaceV(10), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lAddressKey->widget, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), GManager()->SpaceV(10), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lWorkspace->widget, 1, 1, 0);

    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    gtk_widget_show_all(lWidget);

    lWorkspace->AddPage(lWorkspace, "home", "Accueil", GWidget("home")->widget, 1);
    lWorkspace->AddPage(lWorkspace, "home/login", "Connexion", GWidget("login")->widget, 0);
    lWorkspace->AddPage(lWorkspace, "home/sqlite", "SQLite", GWidget("sqlite")->widget, 0);
    lWorkspace->AddPage(lWorkspace, "home/opencv", "OpenCV", GWidget("opencv")->widget, 1);
    lWorkspace->AddPage(lWorkspace, "home/debug", "Debug", GWidget("debug")->widget, 0);
    
    GManager()->SetPage(lWorkspace->GetDefaultKey(lWorkspace));
    
    gtk_window_set_title(GTK_WINDOW(lWidget), lApp->app_name);
    gtk_container_set_border_width(GTK_CONTAINER(lWidget), 0);
    gtk_widget_set_size_request(GTK_WIDGET(lWidget), lApp->win_width, lApp->win_height);
    
    g_signal_connect(G_OBJECT(lWidget), "destroy", G_CALLBACK(GWindow_OnDestroy), NULL);
    g_signal_connect(G_OBJECT(lWidget), "delete_event", G_CALLBACK(GWindow_OnDeleteEvent), NULL);
}
//===============================================
static void GWindow_OnDestroy(GtkWidget* obj, gpointer params) {
    gtk_main_quit();
}
//===============================================
static gboolean GWindow_OnDeleteEvent(GtkWidget* obj, GdkEvent* event, gpointer params) {
    return 0;
}
//===============================================
