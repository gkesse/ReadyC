//===============================================
#define _GMAP_EQUAL_CHAR_
//===============================================
#include "GWindow.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GWindow, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GWindow, GCHAR_PTR, GVOID_PTR)
//===============================================
static void GWindow_Widget(GWidgetO* obj);
static void GWindow_AddPage(GWidgetO* obj, char* key, char* title, GtkWidget* widget, int isDefault);
static void GWindow_SetPage(GWidgetO* obj, char* key);
//===============================================
static void GWindow_destroy(GtkWidget* obj, gpointer params);
static gboolean GWindow_delete_event(GtkWidget* obj, GdkEvent* event, gpointer params);
//===============================================
GWidgetO* GWindow_New() {
    GWidgetO* lParent = GWidget("widget");
    GWindowO* lChild = (GWindowO*)malloc(sizeof(GWindowO));
    
    lChild->parent = lParent;
    lChild->pageMap = 0;
    lChild->pageId = GMap_New(GWindow, GCHAR_PTR, GVOID_PTR)();
    lChild->titleMap = GMap_New(GWindow, GCHAR_PTR, GVOID_PTR)();
    
    lParent->child = lChild;
    
    GWindow_Widget(lParent);
    
    lParent->Delete = GWindow_Delete;
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
    GWindowO* lChild = obj->child;
    sGApp* lApp = GManager()->GetData()->app;
    GtkWidget* lWidget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    obj->widget = lWidget;
    
    GWidgetO* lTitleBar = GWidget("titlebar");
    GWidgetO* lAddressBar = GWidget("addressbar");
    
    GWidgetO* lAddressKey = GWidget("addresskey");
    lAddressKey->SetContent(lAddressKey, "home/debug/clear");

    GWidgetO* lWorkspace = GWidget("stackwidget");
    lChild->pageMap = (void*)lWorkspace;
    
    GtkWidget* lMainLayout = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lTitleBar->widget, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lAddressBar->widget, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lAddressKey->widget, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lWorkspace->widget, 1, 1, 0);

    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    gtk_widget_show_all(lWidget);

    GWindow_AddPage(obj, "home", "Accueil", GWidget("titlebar")->widget, 0);
    GWindow_AddPage(obj, "home/debug", "Accueil", GWidget("addressbar")->widget, 1);
    GWindow_SetPage(obj, "home/debug");

    gtk_window_set_title(GTK_WINDOW(lWidget), lApp->app_name);
    gtk_container_set_border_width(GTK_CONTAINER(lWidget), 0);
    gtk_widget_set_size_request(GTK_WIDGET(lWidget), lApp->win_width, lApp->win_height);
    
    g_signal_connect(G_OBJECT(lWidget), "destroy", G_CALLBACK(GWindow_destroy), NULL);
    g_signal_connect(G_OBJECT(lWidget), "delete_event", G_CALLBACK(GWindow_delete_event), NULL);
}
//===============================================
static void GWindow_AddPage(GWidgetO* obj, char* key, char* title, GtkWidget* widget, int isDefault) {
    GWindowO* lChild = obj->child;
    GMapO(GWindow, GCHAR_PTR, GVOID_PTR)* lPageId = lChild->pageId;
    GMapO(GWindow, GCHAR_PTR, GVOID_PTR)* lTitleMap = lChild->titleMap;
    int lCount = lChild->pageMap->Count(lChild->pageMap);
    lPageId->SetData(lPageId, key, (void*)lCount, GMAP_EQUAL_CHAR);
    lTitleMap->SetData(lTitleMap, key, title, GMAP_EQUAL_CHAR);
    lChild->pageMap->AddWidget(lChild->pageMap, widget);
}
//===============================================
static void GWindow_SetPage(GWidgetO* obj, char* key) {
    GWindowO* lChild = obj->child;
    GMapO(GWindow, GCHAR_PTR, GVOID_PTR)* lPageId = lChild->pageId;
    GMapO(GWindow, GCHAR_PTR, GVOID_PTR)* lTitleMap = lChild->titleMap;
    int lPageIndex = (int)lPageId->GetData(lPageId, key, GMAP_EQUAL_CHAR);
    char* lTitle = (char*)lTitleMap->GetData(lTitleMap, key, GMAP_EQUAL_CHAR);
    lChild->pageMap->SetCurrentIndex(lChild->pageMap, lPageIndex);
}
//===============================================
static void GWindow_destroy(GtkWidget* obj, gpointer params) {
    gtk_main_quit();
}
//===============================================
static gboolean GWindow_delete_event(GtkWidget* obj, GdkEvent* event, gpointer params) {
    return 0;
}
//===============================================
