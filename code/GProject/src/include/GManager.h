//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GManagerO GManagerO;
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGSQLite sGSQLite;
typedef struct _sGJson sGJson;
//===============================================
struct _GManagerO {
    void (*Delete)();
    sGManager* (*DataGet)();
    // global
    void (*Test)(int argc, char** argv);
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
    char* file;
};
//===============================================
struct _sGJson {
    char* file;
};
//===============================================
GManagerO* GManager_New();
void GManager_Delete();
GManagerO* GManager();
//===============================================
#endif
//===============================================