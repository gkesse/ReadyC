//===============================================
#include "GWindowGtk.h"
#include "GManager.h"
//===============================================
static void GWindowGtk_destroy(GtkWidget* obj, gpointer params);
static gboolean GWindowGtk_delete_event(GtkWidget* obj, GdkEvent* event, gpointer params);
//===============================================
GtkWidget* GWindowGtk_New() {
    sGApp* lApp = GManager()->GetData()->app;
    GWindowGtk* lWidget = gtk_type_new(GWindowGtk_Get_Type());
    
    GtkWidget* lWindow = GWidget_Create("window");
        
    GtkWidget* lMainLayout = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lWindow, 1, 1, 0);

    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);

    gtk_window_set_title(GTK_WINDOW(lWidget), lApp->app_name);
    gtk_container_set_border_width(GTK_CONTAINER(lWidget), 0);
    gtk_widget_set_size_request(GTK_WIDGET(lWidget), lApp->win_width, lApp->win_height);
    
    g_signal_connect(G_OBJECT(lWidget), "destroy", G_CALLBACK(GWindowGtk_destroy), NULL);
    g_signal_connect(G_OBJECT(lWidget), "delete_event", G_CALLBACK(GWindowGtk_delete_event), NULL);
                    
    return GTK_WIDGET(lWidget);
}
//===============================================
GtkType GWindowGtk_Get_Type() {
    static GtkType lGWindowGtkType = 0;
    if(!lGWindowGtkType) {
        static const GtkTypeInfo lGWindowGtkInfo = {
            "GWindowGtk",
            sizeof(GWindowGtk),
            sizeof(GWindowGtkClass),
            (GtkClassInitFunc) NULL,
            (GtkObjectInitFunc) NULL,
            NULL,
            NULL,
            (GtkClassInitFunc) NULL
        };
        lGWindowGtkType = gtk_type_unique(gtk_window_get_type(), &lGWindowGtkInfo);
    }
    return lGWindowGtkType;
}
//===============================================
// callback
//===============================================
static void GWindowGtk_destroy(GtkWidget* obj, gpointer params) {
    gtk_main_quit();
}
//===============================================
static gboolean GWindowGtk_delete_event(GtkWidget* obj, GdkEvent* event, gpointer params) {
    return 0;
}
//===============================================
