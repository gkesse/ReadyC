//===============================================
#include "GMySQL.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef MYSQL* GMYSQL_PTR;
typedef MYSQL_RES* GMYSQLRES_PTR;
typedef MYSQL_ROW* GMYSQLROW_PTR;
typedef ulint* GULINT_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GMYSQL_PTR, GMySQL_GCHAR_PTR_GMYSQL_PTR)
GDEFINE_MAP(GCHAR_PTR, GMYSQL_PTR, GMySQL_GCHAR_PTR_GMYSQL_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GMYSQLRES_PTR, GMySQL_GCHAR_PTR_GMYSQLRES_PTR)
GDEFINE_MAP(GCHAR_PTR, GMYSQLRES_PTR, GMySQL_GCHAR_PTR_GMYSQLRES_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GMYSQLROW_PTR, GMySQL_GCHAR_PTR_GMYSQLROW_PTR)
GDEFINE_MAP(GCHAR_PTR, GMYSQLROW_PTR, GMySQL_GCHAR_PTR_GMYSQLROW_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GULINT_PTR, GMySQL_GCHAR_PTR_GULINT_PTR)
GDEFINE_MAP(GCHAR_PTR, GULINT_PTR, GMySQL_GCHAR_PTR_GULINT_PTR)
#endif
//===============================================
static GMySQLO* m_GMySQLO = 0;
//===============================================
static void GMySQL_MallocRow(char* rowName);
static void GMySQL_Version();
static void GMySQL_Init(char* mysqlName);
static void GMySQL_Options(char* mysqlName, int option, void* args);
static void GMySQL_RealConnect(char* mysqlName, char* hostname, char* username, char* password, char* dbname, int port);
static void GMySQL_Query(char* mysqlName, char* sqlQuery);
static void GMySQL_UseResult(char* mysqlName, char* resultName);
static int GMySQL_NumFields(char* resultName);
static int GMySQL_FetchRow(char* resultName, char* rowName);
static void GMySQL_FetchLengths(char* resultName, char* lengthName);
static char* GMySQL_GetRow(char* rowName, int index);
static ulint GMySQL_GetLength(char* lengthName, int index);
static void GMySQL_Close(char* mysqlName);
static void GMySQL_FreeResult(char* resultName);
static void GMySQL_FreeRow(char* rowName);
static void GMySQL_DeleteRowMap(char* rowName);
//===============================================
static void GMySQL_QueryPrint(char* mysqlName, char* resultName, char* rowName, char* lengthName, char* sqlQuery);
//===============================================
#if defined(__unix)
static int GMySQL_MapEqual(char* key1, char* key2);
#endif
//===============================================
GMySQLO* GMySQL_New() {
	GMySQLO* lObj = (GMySQLO*)malloc(sizeof(GMySQLO));

#if defined(__unix)
	lObj->m_mysqlMap = GMap_New_GMySQL_GCHAR_PTR_GMYSQL_PTR();
	lObj->m_resultMap = GMap_New_GMySQL_GCHAR_PTR_GMYSQLRES_PTR();
	lObj->m_rowMap = GMap_New_GMySQL_GCHAR_PTR_GMYSQLROW_PTR();
	lObj->m_lengthMap = GMap_New_GMySQL_GCHAR_PTR_GULINT_PTR();
#endif

	lObj->Delete = GMySQL_Delete;
	lObj->MallocRow = GMySQL_MallocRow;
	lObj->Version = GMySQL_Version;
	lObj->Init = GMySQL_Init;
	lObj->Options = GMySQL_Options;
	lObj->RealConnect = GMySQL_RealConnect;
	lObj->Query = GMySQL_Query;
	lObj->UseResult = GMySQL_UseResult;
	lObj->NumFields = GMySQL_NumFields;
	lObj->FetchRow = GMySQL_FetchRow;
	lObj->FetchLengths = GMySQL_FetchLengths;
	lObj->GetRow = GMySQL_GetRow;
	lObj->GetLength = GMySQL_GetLength;
	lObj->Close = GMySQL_Close;
	lObj->FreeResult = GMySQL_FreeResult;
	lObj->FreeRow = GMySQL_FreeRow;
	lObj->DeleteRowMap = GMySQL_DeleteRowMap;
	lObj->QueryPrint = GMySQL_QueryPrint;
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
static void GMySQL_MallocRow(char* rowName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLROW_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_ROW* lRow = (MYSQL_ROW*)malloc(sizeof(MYSQL_ROW));
	if(lRow == 0) {GConsole()->Print("[ GMySQL ] Error  GMySQL_MallocRow\n"); exit(0);}
	lRowMap->SetData(lRowMap, rowName, lRow, GMySQL_MapEqual);
#endif
}
//===============================================
static void GMySQL_Version() {
#if defined(__unix)
	const char* lVersion = mysql_get_client_info();
	GConsole()->Print("[ GMySQL ] Version : %s\n", lVersion);
#endif
}
//===============================================
static void GMySQL_Init(char* mysqlName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = mysql_init(NULL);
	if(lMysql == 0) {GConsole()->Print("[ GMySQL ] Error  GMySQL_Init: %s\n", mysql_error(lMysql)); exit(0);}
	lMysqlMap->SetData(lMysqlMap, mysqlName, lMysql, GMySQL_MapEqual);
#endif
}
//===============================================
static void GMySQL_Options(char* mysqlName, int option, void* args) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlName, GMySQL_MapEqual);
	int lRes = mysql_options(lMysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if(lRes != 0) {GConsole()->Print("[ GMySQL ] Error  GMySQL_Options: %s\n", mysql_error(lMysql)); exit(0);}
#endif
}
//===============================================
static void GMySQL_RealConnect(char* mysqlName, char* hostname, char* username, char* password, char* dbname, int port) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlName, GMySQL_MapEqual);
	MYSQL* lRes = mysql_real_connect(lMysql, hostname, username, password, dbname, port, 0, 0);
	if(lRes == 0) {GConsole()->Print("[ GMySQL ] Error  GMySQL_RealConnect: %s\n", mysql_error(lMysql)); exit(0);}
#endif
}
//===============================================
static void GMySQL_Query(char* mysqlName, char* sqlQuery) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlName, GMySQL_MapEqual);
	int lRes = mysql_query(lMysql, sqlQuery);
	if(lRes != 0) {GConsole()->Print("[ GMySQL ] Error  GMySQL_Query: %s\n", mysql_error(lMysql)); exit(0);}
#endif
}
//===============================================
static void GMySQL_UseResult(char* mysqlName, char* resultName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	GMapO(GMySQL_GCHAR_PTR_GMYSQLRES_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlName, GMySQL_MapEqual);
	MYSQL_RES* lResult = mysql_use_result(lMysql);
	if(lResult == 0) {GConsole()->Print("[ GMySQL ] Error  GMySQL_Query: %s\n", mysql_error(lMysql)); exit(0);}
	lResultMap->SetData(lResultMap, resultName, lResult, GMySQL_MapEqual);
#endif
}
//===============================================
static int GMySQL_NumFields(char* resultName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLRES_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMySQL_MapEqual);
	int lNumFields = mysql_num_fields(lResult);
	return lNumFields;
#endif
	return 0;
}
//===============================================
static int GMySQL_FetchRow(char* resultName, char* rowName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLRES_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	GMapO(GMySQL_GCHAR_PTR_GMYSQLROW_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMySQL_MapEqual);
	MYSQL_ROW* lRow = lRowMap->GetData(lRowMap, rowName, GMySQL_MapEqual);
	*lRow = mysql_fetch_row(lResult);
	lRowMap->SetData(lRowMap, rowName, lRow, GMySQL_MapEqual);
	if(*lRow == 0) return 0;
	return 1;
#endif
	return 0;
}
//===============================================
static void GMySQL_FetchLengths(char* resultName, char* lengthName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLRES_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	GMapO(GMySQL_GCHAR_PTR_GULINT_PTR)* lLengthMap = m_GMySQLO->m_lengthMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMySQL_MapEqual);
	ulint* lLength = mysql_fetch_lengths(lResult);
	lLengthMap->SetData(lLengthMap, lengthName, lLength, GMySQL_MapEqual);
#endif
}
//===============================================
static char* GMySQL_GetRow(char* rowName, int index) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLROW_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_ROW* lRow = lRowMap->GetData(lRowMap, rowName, GMySQL_MapEqual);
	char* lRowIndex = (*lRow)[index];
	return lRowIndex;
#endif
	return 0;
}
//===============================================
static ulint GMySQL_GetLength(char* lengthName, int index) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GULINT_PTR)* lLengthMap = m_GMySQLO->m_lengthMap;
	ulint* lLength = lLengthMap->GetData(lLengthMap, lengthName, GMySQL_MapEqual);
	uint lLengthIndex = lLength[index];
	return lLengthIndex;
#endif
	return 0;
}
//===============================================
static void GMySQL_Close(char* mysqlName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQL_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlName, GMySQL_MapEqual);
	mysql_close(lMysql);
#endif
}
//===============================================
static void GMySQL_FreeResult(char* resultName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLRES_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMySQL_MapEqual);
	mysql_free_result(lResult);
#endif
}
//===============================================
static void GMySQL_FreeRow(char* rowName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLROW_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_ROW* lRow = lRowMap->GetData(lRowMap, rowName, GMySQL_MapEqual);
	free(lRow);
#endif
}
//===============================================
static void GMySQL_DeleteRowMap(char* rowName) {
#if defined(__unix)
	GMapO(GMySQL_GCHAR_PTR_GMYSQLROW_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	lRowMap->Delete(lRowMap);
#endif
}
//===============================================
static void GMySQL_QueryPrint(char* mysqlName, char* resultName, char* rowName, char* lengthName, char* sqlQuery) {
#if defined(__unix)
	GMySQL_Query(mysqlName, sqlQuery);
	GMySQL_UseResult(mysqlName, resultName);
	int lNumFields = GMySQL_NumFields(resultName);
	while(1) {
		int lFetchRow = GMySQL_FetchRow(resultName, rowName);
		if(lFetchRow == 0) break;
		GMySQL_FetchLengths(resultName, lengthName);
		for(int i = 0; i < lNumFields; i++) {
			char* lRowIndex = GMySQL_GetRow(rowName, i) ? GMySQL_GetRow(rowName, i) : "NULL";
			int lLengthIndex = (int)GMySQL_GetLength(rowName, i);
			GConsole()->Print("[%.*s] ", lLengthIndex, lRowIndex);
		}
		GConsole()->Print("\n");
	}
#endif
}
///===============================================
#if defined(__unix)
static int GMySQL_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
