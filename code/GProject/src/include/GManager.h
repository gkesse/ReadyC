//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
#define B_APP_NAME (64)
#define B_HOME_PATH (256)
#define B_DATA_PATH (256)
#define B_SQLITE_DB (256)
#define B_JSON_FILE (256)
//===============================================
typedef struct _GManagerO GManagerO;
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
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
    // string
    char* (*Copy)(char* strIn);
    void (*ToUpper)(char* strIn, char* strOut);
    void (*ToLower)(char* strIn, char* strOut);
    void (*Trim)(char* strIn, char* strOut);
    int (*SplitCount)(char* strIn, char* sep);
    void (*SplitGet)(char* strIn, char* strOut, char* sep, int index);
    void (*Replace)(char* strIn, char* strOut, const char* pattern, const char* replace);
    // data
    sGManager* m_mgr;
};
//===============================================
struct _sGManager {
    sGApp* app;
    sGSQLite* sqlite;
    sGJson* json;
};
//===============================================
GManagerO* GManager_New();
void GManager_Delete();
GManagerO* GManager();
//===============================================
struct _sGApp {
    char app_name[B_APP_NAME+1];
    char home_path[B_HOME_PATH+1];
    char data_path[B_DATA_PATH+1];
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
#endif
//===============================================