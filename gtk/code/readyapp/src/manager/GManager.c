//===============================================
#include "GManager.h"
//===============================================
static GManagerO* m_GManagerO = 0;
//===============================================
// private
//===============================================
// init
static void GManager_Init(GManagerO* obj);
// data
static sGManager* GManager_GetData();
//===============================================
// constructor
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));
    GManager_Init(lObj);
    lObj->Delete = GManager_Delete;
    lObj->GetData = GManager_GetData;
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
}
//===============================================
// data
//===============================================
static sGManager* GManager_GetData() {
    return m_GManagerO->mgr;
}
//===============================================
