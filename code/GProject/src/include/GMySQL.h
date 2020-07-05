//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GInclude.h"
//===============================================
#if defined(_GUSE_MYSQL_ON_)
//===============================================
typedef struct _GMySQLO GMySQLO;
typedef struct _GMapO_GMySQL_GCHAR_PTR_GVOID_PTR GMapO_GMySQL_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GMySQLO {
    void (*Delete)();
    void (*MallocRow)(char* rowName);
    void (*Version)();
    void (*Init)(char* mysqlId);
    void (*Options)(char* mysqlId, int option, void* args);
    void (*RealConnect)(char* mysqlId, char* hostname, char* username, char* password, char* dbname, int port);
    void (*Query)(char* mysqlId, char* sqlQuery);
    void (*UseResult)(char* mysqlId, char* resultName);
    int (*NumFields)(char* resultName);
    int (*FetchRow)(char* resultName, char* rowName);
    void (*FetchLengths)(char* resultName, char* lengthName);
    char* (*GetRow)(char* rowName, int index);
    ulint (*GetLength)(char* lengthName, int index);
    void (*Close)(char* mysqlId);
    void (*FreeResult)(char* resultName);
    void (*FreeRow)(char* rowName);
    void (*DeleteRowMap)(char* rowName);
    void (*QueryPrint)(char* mysqlId, char* resultName, char* rowName, char* lengthName, char* sqlQuery);
    //===============================================
    GMapO_GMySQL_GCHAR_PTR_GVOID_PTR* m_mysqlMap;
    GMapO_GMySQL_GCHAR_PTR_GVOID_PTR* m_resultMap;
    GMapO(GMySQL_GCHAR_PTR_GVOIDROW_PTR)* m_rowMap;
    GMapO(GMySQL_GCHAR_PTR_GULINT_PTR)* m_lengthMap;
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
