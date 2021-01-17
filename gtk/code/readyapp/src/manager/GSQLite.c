//===============================================
#include "GSQLite.h"
#include "GList.h"
#include "GManager.h"
//===============================================
GDECLARE_LIST(GSQLite, GVOID_PTR)
GDEFINE_LIST(GSQLite, GVOID_PTR)
//===============================================
static GSQLiteO* m_GSQLiteO = 0;
//===============================================
typedef struct _sGSQLiteShow sGSQLiteShow;
typedef struct _sGSQLiteData sGSQLiteData;
//===============================================
struct _sGSQLiteShow {
    int onHeader;
    int onGrid;
    char* widthMap;
    int defaultWidth;
    int colCount;
};
//===============================================
struct _sGSQLiteData {
    void* data;
    int count;
};
//===============================================
static void GSQLite_Init(GSQLiteO* obj);
static void* GSQLite_Open();
static void GSQLite_Exec(char* sqlQuery, void* onExec, void* params);
//===============================================
static void GSQLite_QueryShow(char* sqlQuery, char* widthMap, int defaultWidth);
static void GSQLite_QueryWrite(char* sqlQuery);
static void* GSQLite_QueryValue(char* sqlQuery);
static void* GSQLite_QueryCol(char* sqlQuery);
static void* GSQLite_QueryRow(char* sqlQuery);
static void* GSQLite_QueryMap(char* sqlQuery);
//===============================================
static int GSQLite_OnQueryShow(void* params, int rows, char** values, char** fields);
static int GSQLite_OnQueryValue(void* params, int rows, char** values, char** fields);
static int GSQLite_OnQueryCol(void* params, int rows, char** values, char** fields);
static int GSQLite_OnQueryRow(void* params, int rows, char** values, char** fields);
static int GSQLite_OnQueryMap(void* params, int rows, char** values, char** fields);
//===============================================
GSQLiteO* GSQLite_New() {
	GSQLiteO* lObj = (GSQLiteO*)malloc(sizeof(GSQLiteO));

	lObj->Delete = GSQLite_Delete;
	lObj->QueryShow = GSQLite_QueryShow;
	lObj->QueryWrite = GSQLite_QueryWrite;
	lObj->QueryValue = GSQLite_QueryValue;
	lObj->QueryCol = GSQLite_QueryCol;
	lObj->QueryRow = GSQLite_QueryRow;
	lObj->QueryMap = GSQLite_QueryMap;
    
    GSQLite_Init(lObj);
	return lObj;
}
//===============================================
void GSQLite_Delete() {

}
//===============================================
GSQLiteO* GSQLite() {
	if(m_GSQLiteO == 0) {
		m_GSQLiteO = GSQLite_New();
	}
	return m_GSQLiteO;
}
//===============================================
// method
//===============================================
static void GSQLite_Init(GSQLiteO* obj) {
    char lSqlQuery[256];
    char* lValue;
    GListO(GSQLite, GVOID_PTR)* lList;
    // config_data
    sprintf(lSqlQuery, "\
    create table if not exists config_data (\n\
    config_key text,\n\
    config_value text\n\
    )");
    obj->QueryWrite(lSqlQuery);
    // tables
    sprintf(lSqlQuery, "\
    select type, name, tbl_name, rootpage\n\
    from sqlite_master\n\
    ");
    obj->QueryShow(lSqlQuery, "10;20;20;10", 20);
    // query_value
    sprintf(lSqlQuery, "\
    select type, name, tbl_name, rootpage\n\
    from sqlite_master\n\
    ");
    lValue = obj->QueryValue(lSqlQuery);
    GManager()->Free(lValue);
    // query_col
    sprintf(lSqlQuery, "\
    select type, name, tbl_name, rootpage\n\
    from sqlite_master\n\
    ");
    //
    lList = obj->QueryCol(lSqlQuery);
    lList->Show(lList, lList->ShowChar);
    lList->Delete(lList, 0);
    //
    lList = obj->QueryRow(lSqlQuery);
    lList->Show(lList, lList->ShowChar);
    lList->Delete(lList, 0);
    //
    lList = obj->QueryMap(lSqlQuery);
    lList->Show(lList, lList->ShowCharMap);
    lList->DeleteMap(lList, 0);
}
//===============================================
static void* GSQLite_Open() {
    sGApp* lApp = GManager()->mgr->app;
    sqlite3* lDb;
	int lOk = sqlite3_open(lApp->sqlite_db_path, &lDb);
	if(lOk != SQLITE_OK) {printf("[error] %s() : %s\n", __FUNCTION__, lApp->sqlite_db_path);}
    return lDb; 
}
//===============================================
static void GSQLite_Exec(char* sqlQuery, void* onExec, void* params) {
	sqlite3* lDb = GSQLite_Open();
    char* lError;
	int lOk = sqlite3_exec(lDb, sqlQuery, onExec, params, &lError);
	if(lOk != SQLITE_OK) {printf("[error] %s() : %s\n", __FUNCTION__, lError);}
    sqlite3_close(lDb);
}
//===============================================
static void GSQLite_QueryShow(char* sqlQuery, char* widthMap, int defaultWidth) {
    sGSQLiteShow lParams = {1, 1, widthMap, defaultWidth, 0};
    GSQLite_Exec(sqlQuery, GSQLite_OnQueryShow, &lParams);
    
    if(lParams.colCount > 0) printf("+-");
    for(int i = 0; i < lParams.colCount; i++) {
        if(i != 0) printf("-+-");
        int lWidth = GManager()->GetWidth(widthMap, i, defaultWidth);
        for(int j = 0; j < lWidth; j++) {
            printf("-");
        }
    }
    if(lParams.colCount > 0) printf("-+");
    if(lParams.colCount > 0) printf("\n");
}
//===============================================
static void GSQLite_QueryWrite(char* sqlQuery) {
    GSQLite_Exec(sqlQuery, 0, 0);
}
//===============================================
static void* GSQLite_QueryValue(char* sqlQuery) {
    sGSQLiteData lParams = {0, 0};
    GSQLite_Exec(sqlQuery, GSQLite_OnQueryValue, &lParams);
    return lParams.data;
}
//===============================================
static void* GSQLite_QueryCol(char* sqlQuery) {
    void* lData = GList_New(GSQLite, GVOID_PTR)();
    sGSQLiteData lParams = {lData, 0};
    GSQLite_Exec(sqlQuery, GSQLite_OnQueryCol, &lParams);
    return lData;
}
//===============================================
static void* GSQLite_QueryRow(char* sqlQuery) {
    void* lData = GList_New(GSQLite, GVOID_PTR)();
    sGSQLiteData lParams = {lData, 0};
    GSQLite_Exec(sqlQuery, GSQLite_OnQueryRow, &lParams);
    return lData;
}
//===============================================
static void* GSQLite_QueryMap(char* sqlQuery) {
    void* lData = GList_New(GSQLite, GVOID_PTR)();
    sGSQLiteData lParams = {lData, 0};
    GSQLite_Exec(sqlQuery, GSQLite_OnQueryMap, &lParams);
    return lData;
}
//===============================================
static int GSQLite_OnQueryShow(void* params, int colCount, char** colValue, char** colName) {
	sGSQLiteShow* lParams = (sGSQLiteShow*)params;
    if(lParams->onHeader == 1) {
        printf("+-");
        for(int i = 0; i < colCount; i++) {
            if(i != 0) printf("-+-");
            int lWidth = GManager()->GetWidth(lParams->widthMap, i, lParams->defaultWidth);
            for(int j = 0; j < lWidth; j++) {
                printf("-");
            }
        }
        printf("-+");
        printf("\n");
    }
    if(lParams->onHeader == 1) {
        printf("| ");
        for(int i = 0; i < colCount; i++) {
            if(i != 0) printf(" | ");
            int lWidth = GManager()->GetWidth(lParams->widthMap, i, lParams->defaultWidth);
            printf("%-*s", lWidth, colName[i]);
        }
        printf(" |");
        printf("\n");
    }
    if(lParams->onGrid == 1) {
        printf("+-");
        for(int i = 0; i < colCount; i++) {
            if(i != 0) printf("-+-");
            int lWidth = GManager()->GetWidth(lParams->widthMap, i, lParams->defaultWidth);
            for(int j = 0; j < lWidth; j++) {
                printf("-");
            }
        }
        printf("-+");
        printf("\n");
    } 
    printf("| ");
	for(int i = 0; i < colCount; i++) {
        char* lColValue = colValue[i] ? colValue[i] : "NULL";
        if(i != 0) printf(" | ");
        int lWidth = GManager()->GetWidth(lParams->widthMap, i, lParams->defaultWidth);
        printf("%-*s", lWidth, lColValue);
    }
    printf(" |");
    printf("\n");
    lParams->onHeader = 0;
    lParams->onGrid = 0;
    lParams->colCount = colCount;
	return 0; 
}
//===============================================
static int GSQLite_OnQueryValue(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteData* lParams = params;
    if(lParams->count == 0) {
        lParams->data = GManager()->CopyStr(colValue[0]);
    }
    lParams->count++;
    return 0;
}
//===============================================
static int GSQLite_OnQueryCol(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteData* lParams = params;
    GListO(GSQLite, GVOID_PTR)* lData = lParams->data;
    char* lColValue = colValue[0] ? colValue[0] : "NULL";
    lData->AddData(lData, GManager()->CopyStr(lColValue));
    lParams->count++;
    return 0;
}
//===============================================
static int GSQLite_OnQueryRow(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteData* lParams = params;
    GListO(GSQLite, GVOID_PTR)* lData = lParams->data;
    if(lParams->count == 0) {
        for(int i = 0; i < colCount; i++) {
            char* lColValue = colValue[i] ? colValue[i] : "NULL";
            lData->AddData(lData, GManager()->CopyStr(lColValue));
        }
    }
    lParams->count++;
    return 0;
}
//===============================================
static int GSQLite_OnQueryMap(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteData* lParams = params;
    GListO(GSQLite, GVOID_PTR)* lData = lParams->data;
    GListO(GSQLite, GVOID_PTR)* lRow = GList_New(GSQLite, GVOID_PTR)();
    for(int i = 0; i < colCount; i++) {
        char* lColValue = colValue[i] ? colValue[i] : "NULL";
        lRow->AddData(lRow, GManager()->CopyStr(lColValue));
    }
    lData->AddData(lData, lRow);
    lParams->count++;
    return 0;
}
//===============================================
