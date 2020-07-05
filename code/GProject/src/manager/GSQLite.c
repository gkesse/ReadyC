//===============================================
#include "GSQLite.h"
#include "GMap2.h"
#include "GDir2.h"
//===============================================
#if defined(_GUSE_SQLITE_ON_)
//===============================================
GDECLARE_MAP(GSQLite, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GSQLite, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef int (*GSQLITE_EXEC)(void* params, int rows, char** values, char** fields);
//===============================================
static GSQLiteO* m_GSQLiteO = 0;
//===============================================
static void GSQLite_Version();
static void GSQLite_Open(char* dbId, char* path);
static void GSQLite_Exec(char* dbId, GSQLITE_EXEC onExec, void* params, char* sqlQuery);
static int GSQLite_LastId(char* dbId);
static void GSQLite_PrepareV2(char* dbId, char* sqlQuery);
static void GSQLite_BindInt(char* dbId, char* sqlQuery, int index, int value);
static void GSQLite_BindParameterIndexInt(char* dbId, char* parameterIndex, int value);
static void GSQLite_BindBold(char* dbId, int index, void* data, int size);
static int GSQLite_Step(char* dbId);
static const uchar* GSQLite_ColumnText(char* dbId, int index);
static int GSQLite_ColumnBytes(char* dbId, int index);
static const void* GSQLite_ColumnBold(char* dbId, int index);
static void GSQLite_GetAutocommit(char* dbId);
static void GSQLite_Finalize(char* dbId);
static void GSQLite_Close(char* dbId);
//===============================================
static void GSQLite_ShowTables(char* dbId);
static int GSQLite_ShowTablesCallback(void* params, int rows, char** values, char** fields);
//===============================================
GSQLiteO* GSQLite_New() {
	GSQLiteO* lObj = (GSQLiteO*)malloc(sizeof(GSQLiteO));

    lObj->m_dbMap = GMap_New(GSQLite, GCHAR_PTR, GVOID_PTR)();
    lObj->m_stmtMap = GMap_New(GSQLite, GCHAR_PTR, GVOID_PTR)();

	lObj->Delete = GSQLite_Delete;
	lObj->Version = GSQLite_Version;
	lObj->Open = GSQLite_Open;
	lObj->Exec = GSQLite_Exec;
	lObj->LastId = GSQLite_LastId;
	lObj->PrepareV2 = GSQLite_PrepareV2;
	lObj->BindInt = GSQLite_BindInt;
	lObj->BindParameterIndexInt = GSQLite_BindParameterIndexInt;
	lObj->BindBold = GSQLite_BindBold;
	lObj->Step = GSQLite_Step;
	lObj->ColumnText = GSQLite_ColumnText;
	lObj->ColumnBytes = GSQLite_ColumnBytes;
	lObj->ColumnBold = GSQLite_ColumnBold;
	lObj->GetAutocommit = GSQLite_GetAutocommit;
	lObj->Finalize = GSQLite_Finalize;
	lObj->Close = GSQLite_Close;
	return lObj;
}
//===============================================
void GSQLite_Delete() {
    GSQLiteO* lObj = GSQLite();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSQLiteO = 0;
}
//===============================================
GSQLiteO* GSQLite() {
	if(m_GSQLiteO == 0) {
		m_GSQLiteO = GSQLite_New();
	}
	return m_GSQLiteO;
}
//===============================================
static void GSQLite_Version() {
	const char* lVersion = sqlite3_libversion();
	printf("[GSQLite] SQLite Version : %s\n", lVersion);
}
//===============================================
static void GSQLite_Open(char* dbId, char* path) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	char lPath[256];
    GDir2()->PathC(path, lPath);
    sqlite3* lDb;
	int lOk = sqlite3_open(lPath, &lDb);
	if(lOk != SQLITE_OK) {printf("[GSQLite] Erreur ouverture : %s\n", lPath); exit(0);}
	lDbMap->SetData(lDbMap, dbId, lDb, GMap_EqualChar);
}
//===============================================
static void GSQLite_Exec(char* dbId, GSQLITE_EXEC onExec, void* params, char* sqlQuery) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
    char* lError;
	int lOk = sqlite3_exec(lDb, sqlQuery, onExec, params, &lError);
	if(lOk != SQLITE_OK) {printf("[GSQLite] Erreur execution : %s\n", lError); exit(0);}
}
//===============================================
static int GSQLite_LastId(char* dbId) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	int lLastId = sqlite3_last_insert_rowid(lDb);
	return lLastId;
}
//===============================================
static void GSQLite_PrepareV2(char* dbId, char* sqlQuery) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	sqlite3_stmt* lStmt;
	int lOk = sqlite3_prepare_v2(lDb, sqlQuery, -1, &lStmt, 0);
	if(lOk != SQLITE_OK) {printf("[GSQLite] Error GSQLite_PrepareV2: %s\n", sqlite3_errmsg(lDb)); exit(0); }
	lStmtMap->SetData(lStmtMap, dbId, lStmt, GMap_EqualChar);
}
//===============================================
static void GSQLite_BindInt(char* dbId, char* sqlQuery, int index, int value) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	int lOk = sqlite3_bind_int(lStmt, index, value);
	if(lOk != SQLITE_OK) {printf("[GSQLite] Error GSQLite_BindInt: %s\n", sqlite3_errmsg(lDb)); exit(0); }
}
//===============================================
static void GSQLite_BindParameterIndexInt(char* dbId, char* parameterIndex, int value) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	int lIndex = sqlite3_bind_parameter_index(lStmt, parameterIndex);
	int lOk = sqlite3_bind_int(lStmt, lIndex, value);
	if(lOk != SQLITE_OK) {printf("[GSQLite] Error GSQLite_BindParameterIndexInt: %s\n", sqlite3_errmsg(lDb)); exit(0); }
}
//===============================================
static void GSQLite_BindBold(char* dbId, int index, void* data, int size) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	int lOk = sqlite3_bind_blob(lStmt, index, data, size, SQLITE_STATIC);
	if(lOk != SQLITE_OK) {printf("[GSQLite] Error GSQLite_BindBold: %s\n", sqlite3_errmsg(lDb)); exit(0); }
}
//===============================================
static int GSQLite_Step(char* dbId) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	int lOk = sqlite3_step(lStmt);
	return lOk;
}
//===============================================
static const uchar* GSQLite_ColumnText(char* dbId, int index) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	const uchar* lText = sqlite3_column_text(lStmt, index);
	return lText;
}
//===============================================
static int GSQLite_ColumnBytes(char* dbId, int index) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	int lBytes = sqlite3_column_bytes(lStmt, index);
	return lBytes;
}
//===============================================
static const void* GSQLite_ColumnBold(char* dbId, int index) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	const void* lData = sqlite3_column_blob(lStmt, index);
	return lData;
}
//===============================================
static void GSQLite_GetAutocommit(char* dbId) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	int lAutocommit = sqlite3_get_autocommit(lDb);
	printf("[GSQLite] GetAutocommit: %s\n", lAutocommit);
}
//===============================================
static void GSQLite_Error(char* dbId) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	const char* lError = sqlite3_errmsg(lDb);
	printf("[GSQLite] Error GSQLite_Error: %s\n", lError);
}
//===============================================
static void GSQLite_Finalize(char* dbId) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbId, GMap_EqualChar);
	sqlite3_finalize(lStmt);
}
//===============================================
static void GSQLite_Close(char* dbId) {
	GMapO(GSQLite, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbId, GMap_EqualChar);
	int lOk = sqlite3_close(lDb);
	if(lOk != SQLITE_OK) printf("[GSQLite] Error GSQLite_Close\n");
}
//===============================================
static void GSQLite_ShowTables(char* dbId) {
	m_GSQLiteO->Exec(dbId, GSQLite_ShowTablesCallback, 0,
			"SELECT name FROM sqlite_master "
			"WHERE type = 'table' "
			"ORDER BY 1");
}
//===============================================
static int GSQLite_ShowTablesCallback(void* params, int rows, char** values, char** fields) {
	printf("[ TABLES ]:\n");
	for(int i = 0; i < rows; i++) {
		char* lValue = values[i] ? values[i] : "NULL";
		printf("- %s\n", lValue);
	}
	printf("\n");
	return 0;
}
//===============================================
#endif
//===============================================
