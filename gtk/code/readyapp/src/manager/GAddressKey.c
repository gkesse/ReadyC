//===============================================
#include "GAddressKey.h"
#include "GManager.h"
//===============================================
GtkWidget* GAddressKey_New() {
    GAddressKey* lWidget = gtk_type_new(GAddressKey_Get_Type());
    
    GtkWidget* lLabel = gtk_label_new(0);
    gtk_label_set_text(GTK_LABEL(lLabel), "GAddressKey");
    
    GtkWidget* lMainLayout = gtk_vbox_new(0, 0);
    gtk_box_pack_start_defaults(GTK_BOX(lMainLayout), lLabel);
    
    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    
    return GTK_WIDGET(lWidget);
}
//===============================================
GtkType GAddressKey_Get_Type() {
    static GtkType lGAddressKeyType = 0;
    if(!lGAddressKeyType) {
        static const GtkTypeInfo lGAddressKeyInfo = {
            "GAddressKey",
            sizeof(GAddressKey),
            sizeof(GAddressKeyClass),
          (GtkClassInitFunc) NULL,
          (GtkObjectInitFunc) NULL,
            NULL,
            NULL,
          (GtkClassInitFunc) NULL
        };
        lGAddressKeyType = gtk_type_unique(gtk_hbox_get_type(), &lGAddressKeyInfo);
    }
    return lGAddressKeyType;
}
//===============================================
