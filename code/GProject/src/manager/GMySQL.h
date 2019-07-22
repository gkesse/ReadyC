//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GMySQLO GMySQLO;
typedef struct _GMapO_GMySQL_GCHAR_PTR_GMYSQL_PTR GMapO_GMySQL_GCHAR_PTR_GMYSQL_PTR;
//===============================================
struct _GMySQLO {
    void (*Delete)();
    void (*Version)();
    void (*Init)(char* mysqlName);
    GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* m_mysqlMap;
};
//===============================================
GMySQLO* GMySQL_New();
void GMySQL_Delete();
GMySQLO* GMySQL();
//===============================================
#endif
//===============================================
