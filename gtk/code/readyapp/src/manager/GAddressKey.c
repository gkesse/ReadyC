//===============================================
#include "GAddressKey.h"
#include "GManager.h"
//===============================================
static void GAddressKey_Widget(GWidgetO* obj);
static void GAddressKey_SetContent(GWidgetO* obj, char* text);
//===============================================
GWidgetO* GAddressKey_New() {
    GWidgetO* lParent = GWidget("widget");
    GAddressKeyO* lChild = (GAddressKeyO*)malloc(sizeof(GAddressKeyO));
    
    lChild->parent = lParent;    
    lParent->child = lChild;
    
    GAddressKey_Widget(lParent);
    
    lParent->Delete = GAddressKey_Delete;
    lParent->SetContent = GAddressKey_SetContent;
    return lParent;
}
//===============================================
void GAddressKey_Delete(GWidgetO* obj) {
    GAddressKey_Delete(obj);
}
//===============================================
// method
//===============================================
static void GAddressKey_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_hbox_new(0, 0);
    obj->widget = lWidget;
}
//===============================================
// method
//===============================================
static void GAddressKey_SetContent(GWidgetO* obj, char* text) {
    sGApp* lApp = GManager()->GetData()->app;
    int lCount = GManager()->SplitCount(text, "/");
    for(int i = 0; i < lCount; i++) {
        if(i != 0) {
            GtkWidget* lButton = gtk_button_new();
            gtk_button_set_label(GTK_BUTTON(lButton), ">");
            gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);    
        }
        GManager()->SplitGet(text, lApp->format, "/", i);
        GtkWidget* lButton = gtk_button_new();
        gtk_button_set_label(GTK_BUTTON(lButton), lApp->format);
        gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);    
    }
}
//===============================================
