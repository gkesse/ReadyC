//===============================================
#ifndef _GSQLite_
#define _GSQLite_
//===============================================
#include "GInclude.h"
//===============================================
#if defined(_GUSE_SQLITE_ON_)
//===============================================
typedef struct _GSQLiteO GSQLiteO;
typedef struct _GMapO_GSQLite_GCHAR_PTR_GVOID_PTR GMapO_GSQLite_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GSQLiteO {
    void (*Delete)();
    void (*Version)();
    void (*Open)(char* dbId, char* path);
    void (*Exec)(char* dbId, void* onExec, void* params, char* sqlQuery);
    int (*LastId)(char* dbId);
    void (*PrepareV2)(char* dbId, char* sqlQuery);
    void (*BindInt)(char* dbId, char* sqlQuery, int index, int value);
    void (*BindParameterIndexInt)(char* dbId, char* parameterIndex, int value);
    int (*Step)(char* dbId);
    void (*BindBold)(char* dbId, int index, void* data, int size);
    const uchar* (*ColumnText)(char* dbId, int index);
    int (*ColumnBytes)(char* dbId, int index);
    const void* (*ColumnBold)(char* dbId, int index);
    void (*GetAutocommit)(char* dbId);
    void (*Finalize)(char* dbId);
    void (*Close)(char* dbId);
    //===============================================
    GMapO_GSQLite_GCHAR_PTR_GVOID_PTR* m_dbMap;
    GMapO_GSQLite_GCHAR_PTR_GVOID_PTR* m_stmtMap;
};
//===============================================
GSQLiteO* GSQLite_New();
void GSQLite_Delete();
GSQLiteO* GSQLite();
//===============================================
#endif
//===============================================
#endif
//===============================================
