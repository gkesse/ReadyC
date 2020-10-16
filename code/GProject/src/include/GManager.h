//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
#define B_SQLITE_DB (256)
#define B_JSON_FILE (256)
//===============================================
typedef struct _GManagerO GManagerO;
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGSQLite sGSQLite;
typedef struct _sGJson sGJson;
//===============================================
struct _GManagerO {
    // global
    void* child;
    void (*Delete)();
    void (*Test)(int argc, char** argv);
    void (*DataShow)();
    // terminal
    void (*Printf)(const char* format, ...);
    void (*ReadLine)(char* buffer, int size);
    // data
    sGManager* m_mgr;
};
//===============================================
struct _sGManager {
    sGSQLite* sqlite;
    sGJson* json;
};
//===============================================
struct _sGSQLite {
    char db_path[B_SQLITE_DB+1];
};
//===============================================
struct _sGJson {
    char file[B_JSON_FILE+1];
};
//===============================================
GManagerO* GManager_New();
void GManager_Delete();
GManagerO* GManager();
//===============================================
#endif
//===============================================