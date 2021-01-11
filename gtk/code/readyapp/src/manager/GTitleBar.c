//===============================================
#include "GTitleBar.h"
#include "GManager.h"
//===============================================
GtkWidget* GTitleBar_New() {
    GTitleBar* lWidget = gtk_type_new(GTitleBar_Get_Type());
    
    GtkWidget* lLogo = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lLogo), "lLogo");
    
    GtkWidget* lAppName = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lAppName), "lAppName");
    
    GtkWidget* lTitle = gtk_label_new(0);
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
    
    GtkWidget* lMainLayout = gtk_hbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lLogo, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lAppName, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lTitle, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lFullscreen, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lMinimize, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lMaximize, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lClose, 0, 0, 0);
    
    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    
    return GTK_WIDGET(lWidget);
}
//===============================================
GtkType GTitleBar_Get_Type() {
    static GtkType lGTitleBarType = 0;
    if(!lGTitleBarType) {
        static const GtkTypeInfo lGTitleBarInfo = {
            "GTitleBar",
            sizeof(GTitleBar),
            sizeof(GTitleBarClass),
           (GtkClassInitFunc) NULL,
           (GtkObjectInitFunc) NULL,
            NULL,
            NULL,
           (GtkClassInitFunc) NULL
        };
        lGTitleBarType = gtk_type_unique(gtk_hbox_get_type(), &lGTitleBarInfo);
    }
    return lGTitleBarType;
}
//===============================================
