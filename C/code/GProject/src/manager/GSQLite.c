//===============================================
#include "GSQLite.h"
#include "GConsole.h"
//===============================================
typedef char* GCHAR_PTR;
typedef sqlite3* GSQLITE_PTR;
typedef sqlite3_stmt* GSQLITE_STMT_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSQLITE_PTR, GSQLite_GCHAR_PTR_GSQLITE_PTR)
GDEFINE_MAP(GCHAR_PTR, GSQLITE_PTR, GSQLite_GCHAR_PTR_GSQLITE_PTR)
GDECLARE_MAP(GCHAR_PTR, GSQLITE_STMT_PTR, GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)
GDEFINE_MAP(GCHAR_PTR, GSQLITE_STMT_PTR, GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)
//===============================================
static GSQLiteO* m_GSQLiteO = 0;
//===============================================
static void GSQLite_Version();
static void GSQLite_Open(char* dbName, char* path);
static void GSQLite_Exec(char* dbName, GSQLITE_CALLBACK callback, char* sql);
static int GSQLite_LastId(char* dbName);
static void GSQLite_PrepareV2(char* dbName, char* sql);
static void GSQLite_BindInt(char* dbName, char* sql, int index, int value);
static void GSQLite_BindParameterIndexInt(char* dbName, char* parameterIndex, int value);
static void GSQLite_BindBold(char* dbName, int index, void* data, int size);
static int GSQLite_Step(char* dbName);
static const uchar* GSQLite_ColumnText(char* dbName, int index);
static int GSQLite_ColumnBytes(char* dbName, int index);
static const void* GSQLite_ColumnBold(char* dbName, int index);
static void GSQLite_GetAutocommit(char* dbName);
static void GSQLite_Error(char* dbName);
static void GSQLite_Free();
static void GSQLite_Finalize(char* dbName);
static void GSQLite_Close(char* dbName);
//===============================================
static void GSQLite_ShowTables(char* dbName);
static int GSQLite_ShowTablesCallback(void* unused, int rows, char** values, char** fields);
//===============================================
static int GSQLite_MapEqual(char* key1, char* key2);
//===============================================
GSQLiteO* GSQLite_New() {
    GSQLiteO* lObj = (GSQLiteO*)malloc(sizeof(GSQLiteO));
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
    lObj->Error = GSQLite_Error;
    lObj->Free = GSQLite_Free;
    lObj->Finalize = GSQLite_Finalize;
    lObj->Close = GSQLite_Close;
    //
    lObj->ShowTables = GSQLite_ShowTables;
    //
	lObj->m_dbMap = GMap_New_GSQLite_GCHAR_PTR_GSQLITE_PTR();
	lObj->m_error = 0;
	lObj->m_lastId = -1;
	lObj->m_bytes = -1;
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
	GConsole()->Print("[ SQLITE ] Version: %s\n", lVersion);
}
//===============================================
static void GSQLite_Open(char* dbName, char* path) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb;
	int lOk = sqlite3_open(path, &lDb);
	if(lOk != SQLITE_OK) {GConsole()->Print("[ SQLITE ] Error GSQLite_Open\n"); exit(1);}
	lDbMap->SetData(lDbMap, dbName, lDb, GSQLite_MapEqual);
}
//===============================================
static void GSQLite_Exec(char* dbName, GSQLITE_CALLBACK callback, char* sql) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	char** lError = &m_GSQLiteO->m_error;
	int lOk = sqlite3_exec(lDb, sql, callback, 0, lError);
	if(lOk != SQLITE_OK) {GConsole()->Print("[ SQLITE ] Error GSQLite_Exec: %s\n", *lError); exit(1);}
}
//===============================================
static int GSQLite_LastId(char* dbName) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	int lLastId = sqlite3_last_insert_rowid(lDb);
	return lLastId;
}
//===============================================
static void GSQLite_PrepareV2(char* dbName, char* sql) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	sqlite3_stmt* lStmt;
	int lOk = sqlite3_prepare_v2(lDb, sql, -1, &lStmt, 0);
	if(lOk != SQLITE_OK) {GConsole()->Print("[ SQLITE ] Error GSQLite_PrepareV2: %s\n", sqlite3_errmsg(lDb)); exit(1); }
	lStmtMap->SetData(lStmtMap, dbName, lStmt, GSQLite_MapEqual);
}
//===============================================
static void GSQLite_BindInt(char* dbName, char* sql, int index, int value) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	int lOk = sqlite3_bind_int(lStmt, index, value);
	if(lOk != SQLITE_OK) {GConsole()->Print("[ SQLITE ] Error GSQLite_BindInt: %s\n", sqlite3_errmsg(lDb)); exit(1); }
}
//===============================================
static void GSQLite_BindParameterIndexInt(char* dbName, char* parameterIndex, int value) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	int lIndex = sqlite3_bind_parameter_index(lStmt, parameterIndex);
	int lOk = sqlite3_bind_int(lStmt, lIndex, value);
	if(lOk != SQLITE_OK) {GConsole()->Print("[ SQLITE ] Error GSQLite_BindParameterIndexInt: %s\n", sqlite3_errmsg(lDb)); exit(1); }
}
//===============================================
static void GSQLite_BindBold(char* dbName, int index, void* data, int size) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	int lOk = sqlite3_bind_blob(lStmt, index, data, size, SQLITE_STATIC);
	if(lOk != SQLITE_OK) {GConsole()->Print("[ SQLITE ] Error GSQLite_BindBold: %s\n", sqlite3_errmsg(lDb)); exit(1); }
}
//===============================================
static int GSQLite_Step(char* dbName) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	int lOk = sqlite3_step(lStmt);
	return lOk;
}
//===============================================
static const uchar* GSQLite_ColumnText(char* dbName, int index) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	const uchar* lText = sqlite3_column_text(lStmt, index);
	return lText;
}
//===============================================
static int GSQLite_ColumnBytes(char* dbName, int index) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	int* lBytes = &m_GSQLiteO->m_bytes;
	*lBytes = sqlite3_column_bytes(lStmt, index);
	return *lBytes;
}
//===============================================
static const void* GSQLite_ColumnBold(char* dbName, int index) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	const void* lData = sqlite3_column_blob(lStmt, index);
	return lData;
}
//===============================================
static void GSQLite_GetAutocommit(char* dbName) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	int lAutocommit = sqlite3_get_autocommit(lDb);
	GConsole()->Print("[ SQLITE ] GetAutocommit: %s\n", lAutocommit);
}
//===============================================
static void GSQLite_Error(char* dbName) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	const char* lError = sqlite3_errmsg(lDb);
	GConsole()->Print("[ SQLITE ] Error GSQLite_Error: %s\n", lError);
}
//===============================================
static void GSQLite_Free() {
	char* lError = m_GSQLiteO->m_error;
	sqlite3_free(lError);
}
//===============================================
static void GSQLite_Finalize(char* dbName) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_STMT_PTR)* lStmtMap = m_GSQLiteO->m_stmtMap;
	sqlite3_stmt* lStmt = lStmtMap->GetData(lStmtMap, dbName, GSQLite_MapEqual);
	sqlite3_finalize(lStmt);
}
//===============================================
static void GSQLite_Close(char* dbName) {
	GMapO(GSQLite_GCHAR_PTR_GSQLITE_PTR)* lDbMap = m_GSQLiteO->m_dbMap;
	sqlite3* lDb = lDbMap->GetData(lDbMap, dbName, GSQLite_MapEqual);
	int lOk = sqlite3_close(lDb);
	if(lOk != SQLITE_OK) GConsole()->Print("[ SQLITE ] Error GSQLite_Close\n");
}
//===============================================
static void GSQLite_ShowTables(char* dbName) {
	m_GSQLiteO->Exec(dbName, GSQLite_ShowTablesCallback,
			"SELECT name FROM sqlite_master "
			"WHERE type = 'table' "
			"ORDER BY 1");
}
//===============================================
static int GSQLite_ShowTablesCallback(void* unused, int rows, char** values, char** fields) {
	unused = 0;
	GConsole()->Print("[ TABLES ]:\n");
	for(int i = 0; i < rows; i++) {
		char* lValue = values[i] ? values[i] : "NULL";
		GConsole()->Print("- %s\n", lValue);
	}
	GConsole()->Print("\n");
	return 0;
}
//===============================================
static int GSQLite_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
//===============================================
