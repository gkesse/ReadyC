//===============================================
#include "GMySQL.h"
#include "GMap2.h"
//===============================================
#if defined(_GUSE_MYSQL_ON_)
//===============================================
GDECLARE_MAP(GMySQL, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GMySQL, GCHAR_PTR, GVOID_PTR)
//===============================================
static GMySQLO* m_GMySQLO = 0;
//===============================================
static void GMySQL_MallocRow(char* rowName);
static void GMySQL_Version();
static void GMySQL_Init(char* mysqlId);
static void GMySQL_Options(char* mysqlId, int option, void* args);
static void GMySQL_RealConnect(char* mysqlId, char* hostname, char* username, char* password, char* dbname, int port);
static void GMySQL_Query(char* mysqlId, char* sqlQuery);
static void GMySQL_UseResult(char* mysqlId, char* resultName);
static int GMySQL_NumFields(char* resultName);
static int GMySQL_FetchRow(char* resultName, char* rowName);
static void GMySQL_FetchLengths(char* resultName, char* lengthName);
static char* GMySQL_GetRow(char* rowName, int index);
static ulint GMySQL_GetLength(char* lengthName, int index);
static void GMySQL_Close(char* mysqlId);
static void GMySQL_FreeResult(char* resultName);
static void GMySQL_FreeRow(char* rowName);
static void GMySQL_DeleteRowMap(char* rowName);
//===============================================
static void GMySQL_QueryPrint(char* mysqlId, char* resultName, char* rowName, char* lengthName, char* sqlQuery);
//===============================================
static int GMap_EqualChar(char* key1, char* key2);
//===============================================
GMySQLO* GMySQL_New() {
	GMySQLO* lObj = (GMySQLO*)malloc(sizeof(GMySQLO));

	lObj->m_mysqlMap = GMap_New(GMySQL, GCHAR_PTR, GVOID_PTR)();
	lObj->m_resultMap = GMap_New(GMySQL, GCHAR_PTR, GVOID_PTR)();
	lObj->m_rowMap = GMap_New(GMySQL, GCHAR_PTR, GVOID_PTR)();
	lObj->m_lengthMap = GMap_New(GMySQL, GCHAR_PTR, GVOID_PTR)();

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
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_ROW* lRow = (MYSQL_ROW*)malloc(sizeof(MYSQL_ROW));
	if(lRow == 0) {printf("[GMySQL] Error  GMySQL_MallocRow\n"); exit(0);}
	lRowMap->SetData(lRowMap, rowName, lRow, GMap_EqualChar);
}
//===============================================
static void GMySQL_Version() {
	const char* lVersion = mysql_get_client_info();
	printf("[GMySQL] MySQL Version : %s\n", lVersion);
}
//===============================================
static void GMySQL_Init(char* mysqlId) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = mysql_init(0);
	if(lMysql == 0) {printf("[GMySQL] Erreur initialisation : %s\n", mysql_error(lMysql)); exit(0);}
	lMysqlMap->SetData(lMysqlMap, mysqlId, lMysql, GMap_EqualChar);
}
//===============================================
static void GMySQL_Options(char* mysqlId, int option, void* args) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlId, GMap_EqualChar);
	int lRes = mysql_options(lMysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if(lRes != 0) {printf("[GMySQL] Error  GMySQL_Options: %s\n", mysql_error(lMysql)); exit(0);}
}
//===============================================
static void GMySQL_RealConnect(char* mysqlId, char* hostname, char* username, char* password, char* dbname, int port) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlId, GMap_EqualChar);
	MYSQL* lRes = mysql_real_connect(lMysql, hostname, username, password, dbname, port, 0, 0);
	if(lRes == 0) {printf("[GMySQL] Error  GMySQL_RealConnect: %s\n", mysql_error(lMysql)); exit(0);}
}
//===============================================
static void GMySQL_Query(char* mysqlId, char* sqlQuery) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlId, GMap_EqualChar);
	int lRes = mysql_query(lMysql, sqlQuery);
	if(lRes != 0) {printf("[GMySQL] Error  GMySQL_Query: %s\n", mysql_error(lMysql)); exit(0);}
}
//===============================================
static void GMySQL_UseResult(char* mysqlId, char* resultName) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlId, GMap_EqualChar);
	MYSQL_RES* lResult = mysql_use_result(lMysql);
	if(lResult == 0) {printf("[GMySQL] Error  GMySQL_Query: %s\n", mysql_error(lMysql)); exit(0);}
	lResultMap->SetData(lResultMap, resultName, lResult, GMap_EqualChar);
}
//===============================================
static int GMySQL_NumFields(char* resultName) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMap_EqualChar);
	int lNumFields = mysql_num_fields(lResult);
	return lNumFields;
	return 0;
}
//===============================================
static int GMySQL_FetchRow(char* resultName, char* rowName) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMap_EqualChar);
	MYSQL_ROW* lRow = lRowMap->GetData(lRowMap, rowName, GMap_EqualChar);
	*lRow = mysql_fetch_row(lResult);
	lRowMap->SetData(lRowMap, rowName, lRow, GMap_EqualChar);
	if(*lRow == 0) return 0;
	return 1;
	return 0;
}
//===============================================
static void GMySQL_FetchLengths(char* resultName, char* lengthName) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lLengthMap = m_GMySQLO->m_lengthMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMap_EqualChar);
	ulint* lLength = mysql_fetch_lengths(lResult);
	lLengthMap->SetData(lLengthMap, lengthName, lLength, GMap_EqualChar);
}
//===============================================
static char* GMySQL_GetRow(char* rowName, int index) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_ROW* lRow = lRowMap->GetData(lRowMap, rowName, GMap_EqualChar);
	char* lRowIndex = (*lRow)[index];
	return lRowIndex;
	return 0;
}
//===============================================
static ulint GMySQL_GetLength(char* lengthName, int index) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lLengthMap = m_GMySQLO->m_lengthMap;
	ulint* lLength = lLengthMap->GetData(lLengthMap, lengthName, GMap_EqualChar);
	uint lLengthIndex = lLength[index];
	return lLengthIndex;
	return 0;
}
//===============================================
static void GMySQL_Close(char* mysqlId) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lMysqlMap = m_GMySQLO->m_mysqlMap;
	MYSQL* lMysql = lMysqlMap->GetData(lMysqlMap, mysqlId, GMap_EqualChar);
	mysql_close(lMysql);
}
//===============================================
static void GMySQL_FreeResult(char* resultName) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lResultMap = m_GMySQLO->m_resultMap;
	MYSQL_RES* lResult = lResultMap->GetData(lResultMap, resultName, GMap_EqualChar);
	mysql_free_result(lResult);
}
//===============================================
static void GMySQL_FreeRow(char* rowName) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	MYSQL_ROW* lRow = lRowMap->GetData(lRowMap, rowName, GMap_EqualChar);
	free(lRow);
}
//===============================================
static void GMySQL_DeleteRowMap(char* rowName) {
	GMapO(GMySQL, GCHAR_PTR, GVOID_PTR)* lRowMap = m_GMySQLO->m_rowMap;
	lRowMap->Delete(lRowMap);
}
//===============================================
static void GMySQL_QueryPrint(char* mysqlId, char* resultName, char* rowName, char* lengthName, char* sqlQuery) {
	GMySQL_Query(mysqlId, sqlQuery);
	GMySQL_UseResult(mysqlId, resultName);
	int lNumFields = GMySQL_NumFields(resultName);
	while(1) {
		int lFetchRow = GMySQL_FetchRow(resultName, rowName);
		if(lFetchRow == 0) break;
		GMySQL_FetchLengths(resultName, lengthName);
		for(int i = 0; i < lNumFields; i++) {
			char* lRowIndex = GMySQL_GetRow(rowName, i) ? GMySQL_GetRow(rowName, i) : "NULL";
			int lLengthIndex = (int)GMySQL_GetLength(rowName, i);
			printf("[%.*s] ", lLengthIndex, lRowIndex);
		}
		printf("\n");
	}
}
//===============================================
#endif
//===============================================
