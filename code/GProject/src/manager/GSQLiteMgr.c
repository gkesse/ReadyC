//===============================================
#include "GSQLiteMgr.h"
#include "GManager.h"
//===============================================
#define B_QUERY (256)
//===============================================
static GSQLiteMgrO* m_GSQLiteMgrO = 0;
//===============================================
static void GSQLiteMgr_Test(int argc, char** argv);
static void* GSQLiteMgr_Open();
static void GSQLiteMgr_Exec(void* onExec, void* params, char* sqlQuery);
//===============================================
static void GSQLiteMgr_QueryShow(char* sqlQuery);
//===============================================
static int GSQLiteMgr_OnQueryShow(void* params, int rows, char** values, char** fields);
//===============================================
GSQLiteMgrO* GSQLiteMgr_New() {
	GSQLiteMgrO* lObj = (GSQLiteMgrO*)malloc(sizeof(GSQLiteMgrO));

	lObj->Delete = GSQLiteMgr_Delete;
	lObj->Test = GSQLiteMgr_Test;
	lObj->QueryShow = GSQLiteMgr_QueryShow;
	return lObj;
}
//===============================================
void GSQLiteMgr_Delete() {
    GSQLiteMgrO* lObj = GSQLiteMgr();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSQLiteMgrO = 0;
}
//===============================================
GSQLiteMgrO* GSQLiteMgr() {
	if(m_GSQLiteMgrO == 0) {
		m_GSQLiteMgrO = GSQLiteMgr_New();
	}
	return m_GSQLiteMgrO;
}
//===============================================
static void GSQLiteMgr_Test(int argc, char** argv) {
    char lSqlQuery[B_QUERY+1];
    sprintf(lSqlQuery, "\
    select name from sqlite_master \
    where type='table' \
    ");
    GSQLiteMgr()->QueryShow(lSqlQuery);
} 
//===============================================
static void* GSQLiteMgr_Open() {
    sGManager* lMgr = GManager()->DataGet();
    sGSQLite* lSQLite = lMgr->sqlite;
    sqlite3* lDb;
	int lOk = sqlite3_open(lSQLite->file, &lDb);
	if(lOk != SQLITE_OK) {printf("[GSQLiteMgr] erreur ouverture bdd : GSQLiteMgr_Open : %s\n", lSQLite->file); exit(0);}
    return lDb; 
}
//===============================================
static void GSQLiteMgr_Exec(void* onExec, void* params, char* sqlQuery) {
	sqlite3* lDb = GSQLiteMgr_Open();
    char* lError;
	int lOk = sqlite3_exec(lDb, sqlQuery, onExec, params, &lError);
	if(lOk != SQLITE_OK) {printf("[GSQLiteMgr] erreur execution : GSQLiteMgr_Exec : %s\n", lError); exit(0);}
    sqlite3_close(lDb);
}
//===============================================
static void GSQLiteMgr_QueryShow(char* sqlQuery) {
    GSQLiteMgr_Exec(GSQLiteMgr_OnQueryShow, 0, sqlQuery);
}
//===============================================
static int GSQLiteMgr_OnQueryShow(void* params, int rows, char** values, char** fields) {
	printf("%d : %s : %s\n", rows, values[0], fields[0]);
	return 0; 
}
//===============================================
