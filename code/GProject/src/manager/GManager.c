//===============================================
#include "GManager.h"
//===============================================
#define B_ANSWER (256)
#define B_PATH (256)
//===============================================
#if defined(__unix)
#define B_SQLITE_FILE "/home/osboxes/Programs/ReadyBin/unix/.CONFIG_O.dat"
#define B_JSON_FILE "/home/osboxes/Programs/ReadyC/unix/data/json/menu.json"
//===============================================
#elif defined(__WIN32)
#define B_SQLITE_FILE "C:\\Users\\Admin\\Downloads\\Programs\\ReadyBin\\msys\\.CONFIG_O.dat"
#define B_JSON_FILE "C:\\Users\\Admin\\Downloads\\Programs\\ReadyBin\\msys\\data\\json\\menu.json"
#endif
//===============================================
static GManagerO* m_GManagerO = 0;
//===============================================
static sGManager* GManager_DataGet();
static void GManager_DataClear();
static void GManager_Printf(const char* format, ...);
static void GManager_ReadLine(char* buffer, int size);
//===============================================
static void GManager_Init(GManagerO* obj);
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));
    
    GManager_Init(lObj);
    
    lObj->Delete = GManager_Delete;
    lObj->DataGet = GManager_DataGet;
    lObj->DataClear = GManager_DataClear;
    lObj->Printf = GManager_Printf;
    lObj->ReadLine = GManager_ReadLine;
    return lObj;
}
//===============================================
void GManager_Delete() {
    GManagerO* lObj = GManager();
    if(lObj != 0) {
        free(lObj);
    }
    m_GManagerO = 0;
}
//===============================================
GManagerO* GManager() {
    if(m_GManagerO == 0) {
        m_GManagerO = GManager_New();
    }
    return m_GManagerO;
}
//===============================================
static void GManager_Init(GManagerO* obj) {
    // manager
    obj->m_mgr = (sGManager*)malloc(sizeof(sGManager));
    // sqlite
    obj->m_mgr->sqlite = (sGSQLite*)malloc(sizeof(sGSQLite));
    obj->m_mgr->sqlite->file = (char*)malloc(sizeof(char)*(B_PATH+1));
    sprintf(obj->m_mgr->sqlite->file, "%s", B_SQLITE_FILE);
    // json
    obj->m_mgr->json = (sGJson*)malloc(sizeof(sGJson));
    obj->m_mgr->json->file = (char*)malloc(sizeof(char)*(B_PATH+1));
    sprintf(obj->m_mgr->json->file, "%s", B_JSON_FILE);
}
//===============================================
static sGManager* GManager_DataGet() {
    return m_GManagerO->m_mgr;
}
//===============================================
static void GManager_DataClear() {
    // sqlite
    free(m_GManagerO->m_mgr->sqlite->file);
    free(m_GManagerO->m_mgr->sqlite);
    // json
    free(m_GManagerO->m_mgr->json->file);
    free(m_GManagerO->m_mgr->json);
    // manager
    free(m_GManagerO->m_mgr);
}
//===============================================
static void GManager_Printf(const char* format, ...) {
    va_list lArgs;
    va_start (lArgs, format);
    vprintf (format, lArgs);
    fflush(stdout); 
    va_end (lArgs);
}
//===============================================
static void GManager_ReadLine(char* buffer, int size) {
    fflush(stdout); 
    fgets(buffer, size, stdin); 
    buffer[strlen(buffer)-1] = 0;
}
//===============================================
