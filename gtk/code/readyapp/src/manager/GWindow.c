//===============================================
#include "GWindow.h"
#include "GWidget.h"
#include "GManager.h"
//===============================================
GWidget* GWindow_New() {
    GWindow* lWidget = gtk_type_new(GWindow_Get_Type());
    
    GWidget* lTitleBar = GWidget_Create("titlebar");
    GWidget* lAddressBar = GWidget_Create("addressbar");
    GWidget* lAddressKey = GWidget_Create("addresskey");
    GWidget* lWorkspace = GWidget_Create("stackwidget");
    
    //lAddressKey->SetContent(lAddressKey, "home/sqlite");

    GtkWidget* lMainLayout = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), GTK_WIDGET(lTitleBar), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), GTK_WIDGET(lAddressBar), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), GTK_WIDGET(lAddressKey), 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), GTK_WIDGET(lWorkspace), 1, 1, 0);
    
    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    
    return GWidget_Obj(lWidget);
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
