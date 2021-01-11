//===============================================
#include "GAddressBar.h"
#include "GManager.h"
//===============================================
GtkWidget* GAddressBar_New() {
    GAddressBar* lWidget = gtk_type_new(GAddressBar_Get_Type());
    
    GtkWidget* lLabel = gtk_label_new(0);
    gtk_label_set_text(GTK_LABEL(lLabel), "GAddressBar");
    
    GtkWidget* lMainLayout = gtk_vbox_new(1, 5);
    gtk_box_pack_start_defaults(GTK_BOX(lMainLayout), lLabel);
    
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
        lGAddressBarType = gtk_type_unique(gtk_vbox_get_type(), &lGAddressBarInfo);
    }
    return lGAddressBarType;
}
//===============================================
