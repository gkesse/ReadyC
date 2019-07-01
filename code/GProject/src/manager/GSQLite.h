//===============================================
#ifndef _GSQLite_
#define _GSQLite_
//===============================================
#include "GInclude.h"
#include "GDatabase.h"
#include "GMap.h"
//===============================================
typedef struct _GSQLiteO GSQLiteO;
typedef struct _GMapO_GSQLite_GCHAR_PTR_GSQLITE_PTR GMapO_GSQLite_GCHAR_PTR_GSQLITE_PTR;
typedef struct _GMapO_GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR GMapO_GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR;
//===============================================
struct _GSQLiteO {
	void* m_parent;
    void (*Delete)();
    //===============================================
     GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* m_dbMap;
    GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* m_stmtMap;
    char* m_error;
    int m_lastId;
    int m_bytes;
};
//===============================================
GDatabaseO* GSQLite_New();
void GSQLite_Delete();
GDatabaseO* GSQLite();
//===============================================
#endif
//===============================================
