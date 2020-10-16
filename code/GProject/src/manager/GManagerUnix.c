//===============================================
#include "GManagerUnix.h"
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
static GManagerUnixO* m_GManagerUnixO = 0;
//===============================================
// obj
static void GManagerUnix_Init(GManagerUnixO* obj);
//===============================================
// global
static void GManagerUnix_Test(int argc, char** argv);
//===============================================
// terminal
static void GManagerUnix_Printf(const char* format, ...);
static void GManagerUnix_ReadLine(char* buffer, int size);
//===============================================
GManagerUnixO* GManagerUnix_New() {
    GManagerUnixO* lObj = (GManagerUnixO*)malloc(sizeof(GManagerUnixO));
    
    GManagerUnix_Init(lObj);
    
    // global
    lObj->Delete = GManagerUnix_Delete;
    lObj->Test = GManagerUnix_Test;
    // terminal
    lObj->Printf = GManagerUnix_Printf;
    lObj->ReadLine = GManagerUnix_ReadLine;
    return lObj;
}
//===============================================
void GManagerUnix_Delete() {
    GManagerUnixO* lObj = GManagerUnix();
    if(lObj != 0) {
        free(lObj);
    }
    m_GManagerUnixO = 0;
}
//===============================================
GManagerUnixO* GManagerUnix() {
    if(m_GManagerUnixO == 0) {
        m_GManagerUnixO = GManagerUnix_New();
    }
    return m_GManagerUnixO;
}
//===============================================
// obj
//===============================================
static void GManagerUnix_Init(GManagerUnixO* obj) {
    // manager
    obj->m_mgr = (sGManagerUnix*)malloc(sizeof(sGManagerUnix));
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
static void GManagerUnix_Test(int argc, char** argv) {
    printf("oooooooooooo\n");
}
//===============================================
// terminal
//===============================================
static void GManagerUnix_Printf(const char* format, ...) {
    va_list lArgs;
    va_start (lArgs, format);
    vprintf (format, lArgs);
    fflush(stdout); 
    va_end (lArgs);
}
//===============================================
static void GManagerUnix_ReadLine(char* buffer, int size) {
    fflush(stdout); 
    fgets(buffer, size, stdin); 
    buffer[strlen(buffer)-1] = 0;
}
//===============================================
