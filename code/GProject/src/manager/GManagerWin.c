//===============================================
#include "GManagerWin.h"
//===============================================
static GManagerO* m_GManagerWinO = 0;
//===============================================
static void GManagerWin_Init(GManagerWinO* obj);
//===============================================
GManagerO* GManagerWin_New() {
    GManagerO* lParent = GManager_New();
    GManagerWinO* lChild = (GManagerWinO*)malloc(sizeof(GManagerWinO));
    
    GManagerWin_Init(lChild);
    
    lParent->
    lParent->Delete = GManagerWin_Delete;
    return lObj;
}
//===============================================
void GManagerWin_Delete() {
    GManagerWinO* lObj = GManagerWin();
    if(lObj != 0) {
        free(lObj);
    }
    m_GManagerWinO = 0;
}
//===============================================
GManagerWinO* GManagerWin() {
    if(m_GManagerWinO == 0) {
        m_GManagerWinO = GManagerWin_New();
    }
    return m_GManagerWinO;
}
//===============================================
// obj
//===============================================
static void GManagerWin_Init(GManagerWinO* obj) {
    // manager
    obj->m_mgr = (sGManagerWin*)malloc(sizeof(sGManagerWin));
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
// global
//===============================================
static void GManagerWin_Test(int argc, char** argv) {
    printf("oooooooooooo\n");
}
//===============================================
// terminal
//===============================================
static void GManagerWin_Printf(const char* format, ...) {
    va_list lArgs;
    va_start (lArgs, format);
    vprintf (format, lArgs);
    fflush(stdout); 
    va_end (lArgs);
}
//===============================================
static void GManagerWin_ReadLine(char* buffer, int size) {
    fflush(stdout); 
    fgets(buffer, size, stdin); 
    buffer[strlen(buffer)-1] = 0;
}
//===============================================
