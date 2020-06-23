//===============================================
#ifndef _GDatabase_
#define _GDatabase_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDatabaseO GDatabaseO;
typedef int (*GSQLITE_CALLBACK_EXEC)(void* unused, int rows, char** values, char** fields);
//===============================================
struct _GDatabaseO {
    void* m_child;
    void (*Delete)();
    void (*Version)();
    void (*Open)(char* dbName, char* path);
    void (*Exec)(char* dbName, GSQLITE_CALLBACK_EXEC callback, char* sql);
    int (*LastId)(char* dbName);
    void (*PrepareV2)(char* dbName, char* sql);
    void (*BindInt)(char* dbName, char* sql, int index, int value);
    void (*BindParameterIndexInt)(char* dbName, char* parameterIndex, int value);
    int (*Step)(char* dbName);
    void (*BindBold)(char* dbName, int index, void* data, int size);
    const uchar* (*ColumnText)(char* dbName, int index);
    int (*ColumnBytes)(char* dbName, int index);
    const void* (*ColumnBold)(char* dbName, int index);
    void (*GetAutocommit)(char* dbName);
    void (*Error)(char* dbName);
    void (*Free)();
    void (*Finalize)(char* dbName);
    void (*Close)(char* dbName);
    //===============================================
    void (*ShowTables)(char* dbName);
};
//===============================================
GDatabaseO* GDatabase_New();
void GDatabase_Delete(GDatabaseO* obj);
GDatabaseO* GDatabase();
//===============================================
#endif
//===============================================
