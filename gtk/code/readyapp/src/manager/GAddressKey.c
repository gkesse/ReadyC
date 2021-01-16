//===============================================
#include "GAddressKey.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GAddressKey, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GAddressKey, GCHAR_PTR, GVOID_PTR)
//===============================================
static void GAddressKey_Widget(GWidgetO* obj);
static void GAddressKey_SetContent(GWidgetO* obj, char* text);
//===============================================
static void GAddressKey_OnItemClick(GtkWidget* widget, gpointer params);
//===============================================
GWidgetO* GAddressKey_New() {
    GWidgetO* lParent = GWidget("widget");
    GAddressKeyO* lChild = (GAddressKeyO*)malloc(sizeof(GAddressKeyO));
    
    lChild->parent = lParent;
    lChild->widgetMap = GMap_New(GAddressKey, GCHAR_PTR, GVOID_PTR)();
    
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
static void GAddressKey_SetContent(GWidgetO* obj, char* text) {
    GManager()->ClearLayout(obj->widget);
    GAddressKeyO* lChild = obj->child;
    GMapO(GAddressKey, GCHAR_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    int lCount = GManager()->SplitCount(text, "/");
    char lKey[256];
    char lKeyId[256];
    lKeyId[0] = 0;
    for(int i = 0; i < lCount; i++) {
        if(i != 0) {
            GtkWidget* lButton = GManager()->Button("chevronright", 0, 0, 10);
            gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);    
        }
        
        GManager()->SplitGet(text, lKey, "/", i);

        if(i != 0) {sprintf(lKeyId, "%s/", lKeyId);}
        sprintf(lKeyId, "%s%s", lKeyId, lKey);
        GtkWidget* lButton = GManager()->Button(0, lKey, 0, 0);
        gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);
        lWidgetMap->SetData(lWidgetMap, (void*)lButton, GManager()->CopyStr(lKeyId), 0);
        g_signal_connect(G_OBJECT(lButton), "clicked", G_CALLBACK(GAddressKey_OnItemClick), obj);
    }
}
//===============================================
static void GAddressKey_OnItemClick(GtkWidget* widget, gpointer params) {
    GWidgetO* lObj = (GWidgetO*)params;
    GAddressKeyO* lChild = lObj->child;
    GMapO(GAddressKey, GCHAR_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    char* lPageId = (char*)lWidgetMap->GetData(lWidgetMap, (void*)widget, 0);
    GManager()->SetPage(lPageId);
}
//===============================================
