//===============================================
#define _GMAP_EQUAL_CHAR_
//===============================================
#include "GManager.h"
#include "GMap.h"
//===============================================
GDECLARE_MAP(GManager, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GManager, GCHAR_PTR, GVOID_PTR)
//===============================================
#define B_SPLIT (256)
//===============================================
static GManagerO* m_GManagerO = 0;
//===============================================
// init
static void GManager_Init(GManagerO* obj);
// data
static sGManager* GManager_GetData();
// string
static char* GManager_Copy(char* strIn);
static int GManager_SplitCount(char* strIn, char* sep);
static void GManager_SplitGet(char* strIn, char* strOut, char* sep, int index);
// page
static void GManager_SetPage(char* address);
// layout
static void GManager_ClearLayout(GtkWidget* layout);
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));
    GManager_Init(lObj);
    lObj->Delete = GManager_Delete;
    // data
    lObj->GetData = GManager_GetData;
    // string
    lObj->Copy = GManager_Copy;
    lObj->SplitCount = GManager_SplitCount;
    lObj->SplitGet = GManager_SplitGet;
    // page
    lObj->SetPage = GManager_SetPage;
    // layout
    lObj->ClearLayout = GManager_ClearLayout;
    // obj
    return lObj;
}
//===============================================
void GManager_Delete() {

}
//===============================================
GManagerO* GManager() {
    if(m_GManagerO == 0) {
        m_GManagerO = GManager_New();
    }
    return m_GManagerO;
}
//===============================================
// init
//===============================================
static void GManager_Init(GManagerO* obj) {
    // manager
    obj->mgr = (sGManager*)malloc(sizeof(sGManager));
    // app
    obj->mgr->app = (sGApp*)malloc(sizeof(sGApp));
    obj->mgr->app->app_name = "ReadyApp";
    obj->mgr->app->win_width = 640;
    obj->mgr->app->win_height = 480;
    obj->mgr->app->page_id = GMap_New(GManager, GCHAR_PTR, GVOID_PTR)();
    obj->mgr->app->title_map = GMap_New(GManager, GCHAR_PTR, GVOID_PTR)();
}
//===============================================
// data
//===============================================
static sGManager* GManager_GetData() {
    return m_GManagerO->mgr;
}
//===============================================
// string
//===============================================
static char* GManager_Copy(char* strIn) {
    int lSize = strlen(strIn);
    char* lStr = (char*)malloc(sizeof(char)*(lSize+1));
    strcpy(lStr, strIn);
    return lStr;
}
//===============================================
static int GManager_SplitCount(char* strIn, char* sep) {
    int lPos = 0;
    int lCount = 0;

    while(strIn[lPos] != 0) {
        char lChar = strIn[lPos];
        char* lSearch = strchr(sep, lChar);
        if(lSearch != 0) lCount++;
        lPos++;
    }
    lCount += 1;
    return lCount;
}
//===============================================
static void GManager_SplitGet(char* strIn, char* strOut, char* sep, int index) {
    int lPos = 0;
    int lOut = 0;
    int lCount = 0;
    int lFlag = 0;
    char strIn2[B_SPLIT+1];
    strcpy(strIn2, strIn);

    while(strIn2[lPos] != 0) {
        if(lFlag == 0) {
            if(lCount == index) lFlag = 1;
            else lFlag = 2;
        }
        if(lFlag == 1) {
            char lChar = strIn2[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) break;
            strOut[lOut] = lChar;
            lPos++; lOut++;
        }
        if(lFlag == 2) {
            char lChar = strIn2[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) lCount++;
            lPos++;
            lFlag = 0;
        }
    }
    strOut[lOut] = 0;
}
//===============================================
// page
//===============================================
static void GManager_SetPage(char* address) {
    sGApp* lApp = GManager()->GetData()->app;
    GMapO(GManager, GCHAR_PTR, GVOID_PTR)* lPageId = lApp->page_id;
    GMapO(GManager, GCHAR_PTR, GVOID_PTR)* lTitleMap = lApp->title_map;
    int lPageIndex = (int)lPageId->GetData(lPageId, address, GMAP_EQUAL_CHAR);
    char* lTitle = (char*)lTitleMap->GetData(lTitleMap, address, GMAP_EQUAL_CHAR);
    lApp->page_map->SetCurrentIndex(lApp->page_map, lPageIndex);
    gtk_label_set_text(GTK_LABEL(lApp->title), lTitle);
    lApp->address_key->SetContent(lApp->address_key, address);
    gtk_widget_show_all(lApp->address_key->widget);
}
//===============================================
// layout
//===============================================
static void GManager_ClearLayout(GtkWidget* layout) {
    GList* lChildren = gtk_container_get_children(GTK_CONTAINER(layout));
    for(GList* lChild = lChildren; lChild != 0; lChild = g_list_next(lChild)) {
        gtk_widget_destroy(GTK_WIDGET(lChild->data));
    }
    g_list_free(lChildren);
}
//===============================================
