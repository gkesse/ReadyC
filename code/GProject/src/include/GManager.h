//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GManagerO GManagerO;
typedef struct _GMapO_GManager_GCHAR_PTR_GVOID_PTR GMapO_GManager_GCHAR_PTR_GVOID_PTR;
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGSQLite sGSQLite;
typedef struct _sGJson sGJson;
//===============================================
struct _GManagerO {
    void (*Delete)();
    sGManager* (*DataGet)();
    void (*DataClear)();
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