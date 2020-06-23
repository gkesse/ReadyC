//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
#if defined(_GUSE_MYSQL_ON_)
//===============================================
typedef struct _GMySQLO GMySQLO;
typedef struct _GMapO_GMySQL_GCHAR_PTR_GMYSQL_PTR GMapO_GMySQL_GCHAR_PTR_GMYSQL_PTR;
typedef struct _GMapO_GMySQL_GCHAR_PTR_GMYSQLRES_PTR GMapO_GMySQL_GCHAR_PTR_GMYSQLRES_PTR;
typedef struct _GMapO_GMySQL_GCHAR_PTR_GMYSQLROW_PTR GMapO_GMySQL_GCHAR_PTR_GMYSQLROW_PTR;
typedef struct _GMapO_GMySQL_GCHAR_PTR_GULINT_PTR GMapO_GMySQL_GCHAR_PTR_GULINT_PTR;
//===============================================
struct _GMySQLO {
    void (*Delete)();
    void (*MallocRow)(char* rowName);
    void (*Version)();
    void (*Init)(char* mysqlName);
    void (*Options)(char* mysqlName, int option, void* args);
    void (*RealConnect)(char* mysqlName, char* hostname, char* username, char* password, char* dbname, int port);
    void (*Query)(char* mysqlName, char* sqlQuery);
    void (*UseResult)(char* mysqlName, char* resultName);
    int (*NumFields)(char* resultName);
    int (*FetchRow)(char* resultName, char* rowName);
    void (*FetchLengths)(char* resultName, char* lengthName);
    char* (*GetRow)(char* rowName, int index);
    ulint (*GetLength)(char* lengthName, int index);
    void (*Close)(char* mysqlName);
    void (*FreeResult)(char* resultName);
    void (*FreeRow)(char* rowName);
    void (*DeleteRowMap)(char* rowName);
    void (*QueryPrint)(char* mysqlName, char* resultName, char* rowName, char* lengthName, char* sqlQuery);
#if defined(__unix)
    GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* m_mysqlMap;
    GMapO(GMySQL_GCHAR_PTR_GMYSQLRES_PTR)* m_resultMap;
    GMapO(GMySQL_GCHAR_PTR_GMYSQLROW_PTR)* m_rowMap;
    GMapO(GMySQL_GCHAR_PTR_GULINT_PTR)* m_lengthMap;
#endif
};
//===============================================
GMySQLO* GMySQL_New();
void GMySQL_Delete();
GMySQLO* GMySQL();
//===============================================
#endif
//===============================================
#endif
//===============================================
