//===============================================
#include "GHome.h"
#include "GManager.h"
//===============================================
static void GHome_Widget(GWidgetO* obj);
//===============================================
static void GHome_OnItemClick(GWidgetO* obj);
//===============================================
GWidgetO* GHome_New() {
    GWidgetO* lParent = GWidget("widget");
    GHomeO* lChild = (GHomeO*)malloc(sizeof(GHomeO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;
    
    GHome_Widget(lParent);
    
    lParent->Delete = GHome_Delete;
    lParent->OnItemClick = GHome_OnItemClick;
    return lParent;
}
//===============================================
void GHome_Delete(GWidgetO* obj) {
    GHome_Delete(obj);
}
//===============================================
// method
//===============================================
static void GHome_Widget(GWidgetO* obj) {
    GtkWidget* lWidget = gtk_vbox_new(1, 0);
    obj->widget = lWidget;

    GWidgetO* lListBox = GWidget("listbox");
    lListBox->AddItemClick(lListBox, obj);
    lListBox->AddItem(lListBox, "home/login", "Connexion");
    lListBox->AddItem(lListBox, "home/sqlite", "SQLite");
    lListBox->AddItem(lListBox, "home/opencv", "OpenCV");
    lListBox->AddItem(lListBox, "home/debug", "Debug");
    
    gtk_box_pack_start(GTK_BOX(lWidget), lListBox->widget, 0, 0, 0);
}
//===============================================
static void GHome_OnItemClick(GWidgetO* obj) {
    sGApp* lApp = GManager()->GetData()->app;
    char* lWidgetId = lApp->widget_id;
    GManager()->SetPage(lWidgetId);
}
//===============================================
