//===============================================
#include "GWindow.h"
#include "GWidget.h"
#include "GManager.h"
//===============================================
GtkWidget* GWindow_New() {
    GWindow* lWidget = gtk_type_new(GWindow_Get_Type());
    
    GtkWidget* lTitleBar = GWidget_Create("titlebar");
    GtkWidget* lAddressBar = GWidget_Create("addressbar");
    GtkWidget* lAddressKey = GWidget_Create("addresskey");
    GtkWidget* lWorkspace = GWidget_Create("stackwidget");
    
    GtkWidget* lMainLayout = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lTitleBar, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lAddressBar, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lAddressKey, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lWorkspace, 1, 1, 0);
    
    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    
    return GTK_WIDGET(lWidget);
}
//===============================================
GtkType GWindow_Get_Type() {
    static GtkType lGWindowType = 0;
    if(!lGWindowType) {
        static const GtkTypeInfo lGWindowInfo = {
            "GWindow",
            sizeof(GWindow),
            sizeof(GWindowClass),
            (GtkClassInitFunc) NULL,
            (GtkObjectInitFunc) NULL,
            NULL,
            NULL,
            (GtkClassInitFunc) NULL
        };
        lGWindowType = gtk_type_unique(gtk_vbox_get_type(), &lGWindowInfo);
    }
    return lGWindowType;
}
//===============================================
