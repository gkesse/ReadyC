//===============================================
#include "GAddressKey.h"
#include "GMap.h"
#include "GList.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GAddressKey, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GAddressKey, GVOID_PTR, GVOID_PTR)
//===============================================
GDECLARE_LIST(GAddressKey, GVOID_PTR)
GDEFINE_LIST(GAddressKey, GVOID_PTR)
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
    lChild->widgetMap = GMap_New(GAddressKey, GVOID_PTR, GVOID_PTR)();
    
    lParent->child = lChild;
    lParent->Delete = GAddressKey_Delete;
    lParent->SetContent = GAddressKey_SetContent;
    lParent->OnItemClick = GAddressKey_OnItemClick;
    
    GAddressKey_Widget(lParent);
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
    gtk_widget_set_name(lWidget, "GAddressKey");
}
//===============================================
static void GAddressKey_SetContent(GWidgetO* obj, char* text) {
    GManager()->ClearLayout(obj->widget);
    GAddressKeyO* lChild = obj->child;
    GMapO(GAddressKey, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    GListO(GAddressKey, GVOID_PTR)* lMap = GManager()->Split(text, "/");
    char lKeyId[256]; lKeyId[0] = 0;
    for(int i = 0; i < lMap->Size(lMap); i++) {
        if(i != 0) {
            GtkWidget* lButton = GManager()->Button("chevronright", 0, 0, 12);
            gtk_box_pack_start(GTK_BOX(obj->widget), GManager()->SpaceH(5), 0, 0, 0);
            gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);    
            gtk_box_pack_start(GTK_BOX(obj->widget), GManager()->SpaceH(5), 0, 0, 0);
        }
        
        char* lKey = lMap->GetData(lMap, i);

        if(i != 0) {sprintf(lKeyId, "%s/", lKeyId);}
        sprintf(lKeyId, "%s%s", lKeyId, lKey);
        GtkWidget* lButton = GManager()->Button(0, lKey, 0, 0);
        gtk_box_pack_start(GTK_BOX(obj->widget), lButton, 0, 0, 0);
        lWidgetMap->SetData(lWidgetMap, (void*)lButton, GManager()->CopyStr(lKeyId), 0);
        g_signal_connect(G_OBJECT(lButton), "clicked", G_CALLBACK(obj->OnItemClick), obj);
    }
    lMap->Delete(lMap, 0);
}
//===============================================
static void GAddressKey_OnItemClick(GtkWidget* widget, gpointer params) {
    GWidgetO* lObj = (GWidgetO*)params;
    GAddressKeyO* lChild = lObj->child;
    GMapO(GAddressKey, GVOID_PTR, GVOID_PTR)* lWidgetMap = lChild->widgetMap;
    char* lPageId = (char*)lWidgetMap->GetData(lWidgetMap, (void*)widget, 0);
    GManager()->SetPage(lPageId);
}
//===============================================
