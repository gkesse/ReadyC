//===============================================
// widget
#include "GWidget.h"
#include "GTitleBar.h"
#include "GAddressBar.h"
#include "GAddressKey.h"
#include "GStackWidget.h"
// page
#include "GWindow.h"
#include "GWindowGtk.h"
//===============================================
static void GWidget_SetContent(GWidget* widget, char* text);
//===============================================
GWidget* GWidget_New() {
    GWidget* lWidget = gtk_type_new(GWidget_Get_Type());
    lWidget->SetContent = GWidget_SetContent;
    return GWidget_Obj(lWidget);
}
//===============================================
GtkType GWidget_Get_Type() {
    static GtkType lGWidgetType = 0;
    if(!lGWidgetType) {
        static const GtkTypeInfo lGWidgetInfo = {
            "GWidget",
            sizeof(GWidget),
            sizeof(GWidgetClass),
           (GtkClassInitFunc) NULL,
           (GtkObjectInitFunc) NULL,
            NULL,
            NULL,
           (GtkClassInitFunc) NULL
        };
        lGWidgetType = gtk_type_unique(gtk_widget_get_type(), &lGWidgetInfo);
    }
    return lGWidgetType;
}
//===============================================
GWidget* GWidget_Create(char* key) {
    // widget
    if(!strcmp(key, "widget")) {return GWidget_New();}
    //if(!strcmp(key, "titlebar")) {return GTitleBar_New();}
    //if(!strcmp(key, "addressbar")) {return GAddressBar_New();}
    if(!strcmp(key, "addresskey")) {return GAddressKey_New();}
    //if(!strcmp(key, "stackwidget")) {return GStackWidget_New();}
    // page
    if(!strcmp(key, "window")) {return GWindow_New();}
    if(!strcmp(key, "windowgtk")) {return GWindowGtk_New();}
    // default
    return GWidget_New();
}
//===============================================
// method
//===============================================
static void GWidget_SetContent(GWidget* widget, char* text) {
    printf("hhhhhhhhhhhok\n");
}
//===============================================
