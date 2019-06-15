//===============================================
#ifndef _GSQLite_
#define _GSQLite_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSQLiteO GSQLiteO;
typedef struct _GMapO_GSQLite_GCHAR_PTR_GSQLITE_PTR GMapO_GSQLite_GCHAR_PTR_GSQLITE_PTR;
typedef struct _GMapO_GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR GMapO_GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR;
typedef int (*GSQLITE_CALLBACK)(void* unused, int rows, char** values, char** fields);
//===============================================
struct _GSQLiteO {
    void (*Delete)();
    void (*Version)();
    void (*Open)(char* dbName, char* path);
    void (*Exec)(char* dbName, GSQLITE_CALLBACK callback, char* sql);
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
    //===============================================
    GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* m_dbMap;
    GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* m_stmtMap;
    char* m_error;
    int m_lastId;
    int m_bytes;
};
//===============================================
GSQLiteO* GSQLite_New();
void GSQLite_Delete();
GSQLiteO* GSQLite();
//===============================================
#endif
//===============================================
