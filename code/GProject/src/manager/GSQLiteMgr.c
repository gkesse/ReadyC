//===============================================
#include "GSQLiteMgr.h"
#include "GStringMgr.h"
#include "GManager.h"
//===============================================
#define B_QUERY (256)
#define B_WIDTH (8)
//===============================================
static GSQLiteMgrO* m_GSQLiteMgrO = 0;
//===============================================
typedef struct _sGSQLiteShow sGSQLiteShow;
//===============================================
struct _sGSQLiteShow {
    int onHeader;
    int onGrid;
    char* width;
    int widthD;
};
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
    sprintf(lSqlQuery, "\
    select * from CONFIG_DATA \
    limit 5 \
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
    sGSQLiteShow lParams = {1, 1, "20;50", 20};
    
    GSQLiteMgr_Exec(GSQLiteMgr_OnQueryShow, &lParams, sqlQuery);
    
    int lWidthC = GStringMgr()->SplitCount(lParams.width, ";");
    char lWidthG[B_WIDTH+1];

    printf("+-");
    for(int i = 0; i < 2; i++) {
        int lWidth = lParams.widthD;
        if(i < lWidthC) {
            GStringMgr()->SplitGet(lParams.width, lWidthG, ";", i);
            lWidth = atoi(lWidthG);
        }
        if(i != 0) printf("-+-");
        for(int j = 0; j < lWidth; j++) {
            printf("-");
        }
    }
    printf("-+");
    printf("\n");
}
//===============================================
static int GSQLiteMgr_OnQueryShow(void* params, int colCount, char** colValue, char** colName) {
	sGSQLiteShow* lParams = (sGSQLiteShow*)params;

    int lWidthC = GStringMgr()->SplitCount(lParams->width, ";");
    char lWidthG[B_WIDTH+1];
    
    if(lParams->onHeader == 1) {
        printf("+-");
        for(int i = 0; i < colCount; i++) {
            int lWidth = lParams->widthD;
            if(i < lWidthC) {
                GStringMgr()->SplitGet(lParams->width, lWidthG, ";", i);
                lWidth = atoi(lWidthG);
            }
            if(i != 0) printf("-+-");
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
            int lWidth = lParams->widthD;
            if(i < lWidthC) {
                GStringMgr()->SplitGet(lParams->width, lWidthG, ";", i);
                lWidth = atoi(lWidthG);
            }
            if(i != 0) printf(" | ");
            printf("%-*s", lWidth, colName[i]);
        }
        printf(" |");
        printf("\n");
    }
    if(lParams->onGrid == 1) {
        printf("+-");
        for(int i = 0; i < colCount; i++) {
            int lWidth = lParams->widthD;
            if(i < lWidthC) {
                GStringMgr()->SplitGet(lParams->width, lWidthG, ";", i);
                lWidth = atoi(lWidthG);
            }
            if(i != 0) printf("-+-");
            for(int j = 0; j < lWidth; j++) {
                printf("-");
            }
        }
        printf("-+");
        printf("\n");
    } 
    printf("| ");
	for(int i = 0; i < colCount; i++) {
        int lWidth = lParams->widthD;
        if(i < lWidthC) {
            GStringMgr()->SplitGet(lParams->width, lWidthG, ";", i);
            lWidth = atoi(lWidthG);
        }
        char* lColValue = colValue[i] ? colValue[i] : "NULL";
        if(i != 0) printf(" | ");
        printf("%-*s", lWidth, lColValue);
    }
    printf(" |");
    printf("\n");
    lParams->onHeader = 0;
    lParams->onGrid = 0;
	return 0; 
}
//===============================================
