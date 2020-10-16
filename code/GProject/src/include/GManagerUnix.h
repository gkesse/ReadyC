//===============================================
#ifndef _GManagerUnix_
#define _GManagerUnix_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GManagerUnixO GManagerUnixO;
//===============================================
typedef struct _sGManagerUnix sGManagerUnix;
typedef struct _sGSQLite sGSQLite;
typedef struct _sGJson sGJson;
//===============================================
struct _GManagerUnixO {
    void (*Delete)();
    sGManagerUnix* (*DataGet)();
    // global
    void (*Test)(int argc, char** argv);
    // terminal
    void (*Printf)(const char* format, ...);
    void (*ReadLine)(char* buffer, int size);
    // data
    sGManagerUnix* m_mgr;
};
//===============================================
struct _sGManagerUnix {
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
GManagerUnixO* GManagerUnix_New();
void GManagerUnix_Delete();
GManagerUnixO* GManagerUnix();
//===============================================
#endif
//===============================================