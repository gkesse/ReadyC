//===============================================
#include "GGtk.h"
#include "GWidget.h"
#include "GManager.h"
#include "GPicto.h"
//===============================================
static GGtkO* m_GGtkO = 0;
//===============================================
static void GGtk_Test(int argc, char** argv);
static void GGtk_Run(int argc, char** argv);
//===============================================
static void GGtk_OnDestroy(GtkWidget* obj, gpointer params);
static gboolean GGtk_OnDeleteEvent(GtkWidget* obj, GdkEvent* event, gpointer params);
//===============================================
GGtkO* GGtk_New() {
    GGtkO* lObj =(GGtkO*)malloc(sizeof(GGtkO));
    lObj->Delete = GGtk_Delete;
    lObj->Test = GGtk_Test;
    lObj->Run = GGtk_Run;
    return lObj;
}
//===============================================
void GGtk_Delete() {

}
//===============================================
GGtkO* GGtk() {
    if(m_GGtkO == 0) {
        m_GGtkO = GGtk_New();
    }
    return m_GGtkO;
}
//===============================================
void GGtk_Test(int argc, char** argv) {
    gtk_init(&argc, &argv);
    
    GtkWidget* lWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    GtkWidget* lLabel = gtk_label_new(0);
    gtk_label_set_text(GTK_LABEL(lLabel), "Bonjour tout le monde");
    
    GtkWidget* lMainLayout = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lLabel, 1, 1, 0);

    gtk_container_add(GTK_CONTAINER(lWindow), lMainLayout);
    gtk_widget_show_all(lWindow);
    
    gtk_window_set_title(GTK_WINDOW(lWindow), "ReadyApp");
    gtk_container_set_border_width(GTK_CONTAINER(lWindow), 0);
    gtk_widget_set_size_request(GTK_WIDGET(lWindow), 600, 330);
    
    g_signal_connect(G_OBJECT(lWindow), "destroy", G_CALLBACK(GGtk_OnDestroy), NULL);
    g_signal_connect(G_OBJECT(lWindow), "delete_event", G_CALLBACK(GGtk_OnDeleteEvent), NULL);
    
    gtk_main();
}
//===============================================
static void GGtk_OnDestroy(GtkWidget* obj, gpointer params) {
    gtk_main_quit();
}
//===============================================
static gboolean GGtk_OnDeleteEvent(GtkWidget* obj, GdkEvent* event, gpointer params) {
    return 0;
}
//===============================================
static void GGtk_Run(int argc, char** argv) {
    gtk_init(&argc, &argv);

    GManager()->LoadStyle();
    GManager()->LoadImg();
    GManager()->LoadData();
    GPicto()->Load();
    GWidget("window");

    gtk_main();
}
//===============================================
