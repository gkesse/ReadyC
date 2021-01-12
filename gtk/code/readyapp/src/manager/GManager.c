//===============================================
#include "GManager.h"
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
