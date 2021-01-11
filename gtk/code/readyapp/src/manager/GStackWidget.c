//===============================================
#include "GStackWidget.h"
#include "GManager.h"
//===============================================
GtkWidget* GStackWidget_New() {
    GStackWidget* lWidget = gtk_type_new(GStackWidget_Get_Type());
    
    GtkWidget* lLabel = gtk_label_new(0);
    gtk_label_set_text(GTK_LABEL(lLabel), "GStackWidget");
    
    GtkWidget* lMainLayout = gtk_vbox_new(1, 5);
    gtk_box_pack_start_defaults(GTK_BOX(lMainLayout), lLabel);
    
    gtk_container_add(GTK_CONTAINER(lWidget), lMainLayout);
    
    return GTK_WIDGET(lWidget);
}
//===============================================
GtkType GStackWidget_Get_Type() {
    static GtkType lGStackWidgetType = 0;
    if(!lGStackWidgetType) {
        static const GtkTypeInfo lGStackWidgetInfo = {
            "GStackWidget",
            sizeof(GStackWidget),
            sizeof(GStackWidgetClass),
          (GtkClassInitFunc) NULL,
          (GtkObjectInitFunc) NULL,
            NULL,
            NULL,
          (GtkClassInitFunc) NULL
        };
        lGStackWidgetType = gtk_type_unique(gtk_vbox_get_type(), &lGStackWidgetInfo);
    }
    return lGStackWidgetType;
}
//===============================================
