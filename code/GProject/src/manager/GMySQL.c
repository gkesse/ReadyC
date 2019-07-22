//===============================================
#include "GMySQL.h"
#include "GConsole.h"
//===============================================
typedef char* GCHAR_PTR;
typedef MYSQL* GMYSQL_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GMYSQL_PTR, GMySQL_GCHAR_PTR_GMYSQL_PTR)
GDEFINE_MAP(GCHAR_PTR, GMYSQL_PTR, GMySQL_GCHAR_PTR_GMYSQL_PTR)
//===============================================
static GMySQLO* m_GMySQLO = 0;
//===============================================
static void GMySQL_Version();
static void GMySQL_Init(char* mysqlName);
//===============================================
static int GMySQL_MapEqual(char* key1, char* key2);
//===============================================
GMySQLO* GMySQL_New() {
	GMySQLO* lObj = (GMySQLO*)malloc(sizeof(GMySQLO));

	lObj->m_mysqlMap = GMap_New_GMySQL_GCHAR_PTR_GMYSQL_PTR();

	lObj->Delete = GMySQL_Delete;
	lObj->Version = GMySQL_Version;
	lObj->Version = GMySQL_Init;
	return lObj;
}
//===============================================
void GMySQL_Delete() {
	GMySQLO* lObj = GMySQL();
	if(lObj != 0) {
		free(lObj);
	}
	m_GMySQLO = 0;
}
//===============================================
GMySQLO* GMySQL() {
	if(m_GMySQLO == 0) {
		m_GMySQLO = GMySQL_New();
	}
	return m_GMySQLO;
}
//===============================================
static void GMySQL_Version() {
	const char* lVersion = mysql_get_client_info();
	GConsole()->Print("[ GMySQL ] Version : %s\n", lVersion);
}
//===============================================
static void GMySQL_Init(char* mysqlName) {
	GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = mysql_init(NULL);
	if(lMysql == 0) {GConsole()->Print("[ GMySQL ] Error  GMySQL_Init: %s\n", mysql_error(lMysql)); exit(0);}
	lMysqlMap->SetData(lMysqlMap, mysqlName, lMysql, GMySQL_MapEqual);
}
//===============================================
static int GMySQL_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
//===============================================
