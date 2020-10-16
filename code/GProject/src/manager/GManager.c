//===============================================
#include "GManager.h"
#include "GManagerUnix.h"
#include "GManagerWin.h"
//===============================================
// obj
static void GManager_Init(GManagerO* obj);
//===============================================
// global
static void GManager_Test(int argc, char** argv);
static void GManager_DataShow();
//===============================================
// terminal
static void GManager_Printf(const char* format, ...);
static void GManager_ReadLine(char* buffer, int size);
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));
    
    GManager_Init(lObj);
    
    // global
    lObj->child = 0;
    lObj->Delete = GManager_Delete;
    lObj->Test = GManager_Test;
    lObj->DataShow = GManager_DataShow;
    // terminal
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
}
//===============================================
GManagerO* GManager() {
#if defined(__unix)
    return GManagerUnix();
#elif defined(__WIN32)
    return GManagerWin();
#endif
    return 0;
}
//===============================================
// obj
//===============================================
static void GManager_Init(GManagerO* obj) {
    // manager
    obj->m_mgr = (sGManager*)malloc(sizeof(sGManager));
    // app
    obj->m_mgr->app = (sGApp*)malloc(sizeof(sGApp));
    strcpy(obj->m_mgr->app->app_name, "ReadyApp");
    strcpy(obj->m_mgr->app->home_path, "UNKNOWN");
    // sqlite
    obj->m_mgr->sqlite = (sGSQLite*)malloc(sizeof(sGSQLite));
    strcpy(obj->m_mgr->sqlite->db_path, "UNKNOWN");
    // json
    obj->m_mgr->json = (sGJson*)malloc(sizeof(sGJson));
    strcpy(obj->m_mgr->json->file, "UNKNOWN");
}
//===============================================
// global
//===============================================
static void GManager_Test(int argc, char** argv) {
    GManager()->DataShow();
}
//===============================================
static void GManager_DataShow() {
    int lWidth = -50;
    printf("\n");
    printf("#================================================\n");
    printf("[info] GManager()->m_mgr->app\n");
    printf("#================================================\n");
    printf("\n");
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->app->app_name", GManager()->m_mgr->app->app_name);
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->app->home_path", GManager()->m_mgr->app->home_path);
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->app->data_path", GManager()->m_mgr->app->data_path);
    printf("\n");
    printf("#================================================\n");
    printf("[info] GManager()->m_mgr->sqlite\n");
    printf("#================================================\n");
    printf("\n");
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->sqlite->db_path", GManager()->m_mgr->sqlite->db_path);
    printf("\n");
    printf("#================================================\n");
    printf("[info] GManager()->m_mgr->json\n");
    printf("#================================================\n");
    printf("\n");
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->json->file", GManager()->m_mgr->json->file);
    printf("\n");
}
//===============================================
// terminal
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
