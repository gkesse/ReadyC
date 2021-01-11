//===============================================
#include "GAddressBar.h"
#include "GManager.h"
//===============================================
GtkWidget* GAddressBar_New() {
    GAddressBar* lWidget = gtk_type_new(GAddressBar_Get_Type());
    
    GtkWidget* lIcon = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lIcon), "lIcon");
    
    GtkWidget* lEdit = gtk_entry_new ();
    
    GtkWidget* lGoTo = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(lGoTo), "lGoTo");
    
    GtkWidget* lMainLayout = gtk_hbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lIcon, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lEdit, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(lMainLayout), lGoTo, 0, 0, 0);
    
    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    
    return GTK_WIDGET(lWidget);
}
//===============================================
GtkType GAddressBar_Get_Type() {
    static GtkType lGAddressBarType = 0;
    if(!lGAddressBarType) {
        static const GtkTypeInfo lGAddressBarInfo = {
            "GAddressBar",
            sizeof(GAddressBar),
            sizeof(GAddressBarClass),
           (GtkClassInitFunc) NULL,
           (GtkObjectInitFunc) NULL,
            NULL,
            NULL,
           (GtkClassInitFunc) NULL
        };
        lGAddressBarType = gtk_type_unique(gtk_hbox_get_type(), &lGAddressBarInfo);
    }
    return lGAddressBarType;
}
//===============================================
