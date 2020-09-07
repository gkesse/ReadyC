//===============================================
#include "GSQLiteMgr.h"
#include "GStringMgr.h"
#include "GManager.h"
//===============================================
#define B_QUERY (256)
#define B_WIDTH (8)
#define B_VALUE (256)
//===============================================
static GSQLiteMgrO* m_GSQLiteMgrO = 0;
//===============================================
typedef struct _sGSQLiteShow sGSQLiteShow;
typedef struct _sGSQLiteValue sGSQLiteValue;
typedef struct _sGSQLiteCol sGSQLiteCol;
typedef struct _sGSQLiteRow sGSQLiteRow;
//===============================================
struct _sGSQLiteShow {
    int onHeader;
    int onGrid;
    char* width;
    int widthD;
};
//===============================================
struct _sGSQLiteValue {
    char* value;
    int count;
    int index;
};
//===============================================
struct _sGSQLiteCol{
    char* col;
    char* sep;
    int count;
};
//===============================================
struct _sGSQLiteRow {
    char* row;
    char* sep;
    int count;
    int index;
};
//===============================================
static void GSQLiteMgr_Test(int argc, char** argv);
static void* GSQLiteMgr_Open();
static void GSQLiteMgr_Exec(void* onExec, void* params, char* sqlQuery);
//===============================================
static void GSQLiteMgr_QueryShow(char* sqlQuery, char* width, int widthD);
static void GSQLiteMgr_QueryWrite(char* sqlQuery);
static void GSQLiteMgr_QueryValue(char* sqlQuery, char* value);
static void GSQLiteMgr_QueryCol(char* sqlQuery, char* col, char* sep);
static void GSQLiteMgr_QueryRow(char* sqlQuery, char* row, char* sep);
//===============================================
static int GSQLiteMgr_OnQueryShow(void* params, int rows, char** values, char** fields);
static int GSQLiteMgr_OnQueryValue(void* params, int rows, char** values, char** fields);
static int GSQLiteMgr_OnQueryCol(void* params, int rows, char** values, char** fields);
static int GSQLiteMgr_OnQueryRow(void* params, int rows, char** values, char** fields);
//===============================================
GSQLiteMgrO* GSQLiteMgr_New() {
	GSQLiteMgrO* lObj = (GSQLiteMgrO*)malloc(sizeof(GSQLiteMgrO));

	lObj->Delete = GSQLiteMgr_Delete;
	lObj->Test = GSQLiteMgr_Test;
	lObj->QueryShow = GSQLiteMgr_QueryShow;
	lObj->QueryWrite = GSQLiteMgr_QueryWrite;
	lObj->QueryValue = GSQLiteMgr_QueryValue;
	lObj->QueryCol = GSQLiteMgr_QueryCol;
	lObj->QueryRow = GSQLiteMgr_QueryRow;
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
    char lValue[B_VALUE+1];

    /*sprintf(lSqlQuery, "\
    insert into CONFIG_DATA (CONFIG_KEY, CONFIG_VALUE)\
    values ('%s', '%s') \
    ", "G_MY_KEY", "MY_VALUE");
    GSQLiteMgr()->QueryWrite(lSqlQuery);*/

    sprintf(lSqlQuery, "\
    select * from CONFIG_DATA \
    limit 5 \
    ");
    GSQLiteMgr()->QueryShow(lSqlQuery, "20;30", 25);
    printf("\n");
    
    sprintf(lSqlQuery, "\
    select CONFIG_VALUE from CONFIG_DATA \
    where CONFIG_KEY = 'G_DEPOT_ROOT' \
    ");
    GSQLiteMgr()->QueryValue(lSqlQuery, lValue);
    printf("%s\n", lValue);
    printf("\n");
    
    sprintf(lSqlQuery, "\
    select CONFIG_KEY from CONFIG_DATA \
    limit 5 \
    ");
    GSQLiteMgr()->QueryCol(lSqlQuery, lValue, "|");
    printf("%s\n", lValue);
    printf("\n");
    
    sprintf(lSqlQuery, "\
    select * from CONFIG_DATA \
    where CONFIG_KEY = 'G_MY_KEY' \
    ");
    GSQLiteMgr()->QueryRow(lSqlQuery, lValue, "|");
    printf("%s\n", lValue);
    printf("\n");

    /*sprintf(lSqlQuery, "\
    delete from CONFIG_DATA\
    where CONFIG_KEY = '%s' \
    ", "G_MY_KEY");
    GSQLiteMgr()->QueryWrite(lSqlQuery);*/
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
static void GSQLiteMgr_QueryShow(char* sqlQuery, char* width, int widthD) {
    sGSQLiteShow lParams = {1, 1, width, widthD};
    
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
static void GSQLiteMgr_QueryWrite(char* sqlQuery) {
    GSQLiteMgr_Exec(0, 0, sqlQuery);
}
//===============================================
static void GSQLiteMgr_QueryValue(char* sqlQuery, char* value) {
    sGSQLiteValue lParams = {value, 0, 0};
    GSQLiteMgr_Exec(GSQLiteMgr_OnQueryValue, &lParams, sqlQuery);
}
//===============================================
static void GSQLiteMgr_QueryCol(char* sqlQuery, char* col, char* sep) {
    col[0] = 0;
    sGSQLiteCol lParams = {col, sep, 0};
    GSQLiteMgr_Exec(GSQLiteMgr_OnQueryCol, &lParams, sqlQuery);
}
//===============================================
static void GSQLiteMgr_QueryRow(char* sqlQuery, char* row, char* sep) {
    row[0] = 0;
    sGSQLiteRow lParams = {row, sep, 0, 0};
    GSQLiteMgr_Exec(GSQLiteMgr_OnQueryRow, &lParams, sqlQuery);
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
static int GSQLiteMgr_OnQueryValue(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteValue* lParams = (sGSQLiteValue*)params;
    if(lParams->count == lParams->index) {
        strcpy(lParams->value, colValue[0]);
    }
    lParams->count++;
    return 0;
}
//===============================================
static int GSQLiteMgr_OnQueryCol(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteCol* lParams = (sGSQLiteCol*)params;
    if(lParams->count != 0) {
        strcat(lParams->col, lParams->sep);
    }
    char* lColValue = colValue[0] ? colValue[0] : "NULL";
    strcat(lParams->col, lColValue);
    lParams->count++;
    return 0;
}
//===============================================
static int GSQLiteMgr_OnQueryRow(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteRow* lParams = (sGSQLiteRow*)params;
    if(lParams->count == lParams->index) {
        for(int i = 0; i < colCount; i++) {
            char* lColValue = colValue[i] ? colValue[i] : "NULL";
            if(i != 0) strcat(lParams->row, lParams->sep);
            strcat(lParams->row, lColValue);
        }
    }
    lParams->count++;
    return 0;
}
//===============================================
