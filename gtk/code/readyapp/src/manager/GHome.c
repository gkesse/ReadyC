//===============================================
#include "GHome.h"
#include "GManager.h"
//===============================================
static void GHome_Widget(GWidgetO* obj);
//===============================================
static void GHome_OnItemClickObs(GWidgetO* obj);
//===============================================
GWidgetO* GHome_New() {
    GWidgetO* lParent = GWidget("widget");
    GHomeO* lChild = (GHomeO*)malloc(sizeof(GHomeO));
    
    lChild->parent = lParent;
    
    lParent->child = lChild;    
    lParent->Delete = GHome_Delete;
    lParent->OnItemClickObs = GHome_OnItemClickObs;
    
    GHome_Widget(lParent);
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
    lListBox->AddItem(lListBox, "home/login", "Connexion", "user");
    lListBox->AddItem(lListBox, "home/sqlite", "SQLite", "database");
    lListBox->AddItem(lListBox, "home/opencv", "OpenCV", "camera");
    lListBox->AddItem(lListBox, "home/debug", "Debug", "filetexto");
    
    gtk_box_pack_start(GTK_BOX(lWidget), lListBox->widget, 0, 0, 0);
}
//===============================================
static void GHome_OnItemClickObs(GWidgetO* obj) {
    sGApp* lApp = GManager()->GetData()->app;
    char* lWidgetId = lApp->widget_id;
    GManager()->SetPage(lWidgetId);
}
//===============================================
