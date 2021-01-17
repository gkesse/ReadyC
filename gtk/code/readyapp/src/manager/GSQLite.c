//===============================================
#include "GSQLite.h"
#include "GManager.h"
//===============================================
#define B_QUERY (256)
#define B_WIDTH (8)
#define B_VALUE (256)
//===============================================
static GSQLiteO* m_GSQLiteO = 0;
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
    int colCount;
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
static void GSQLite_Test(int argc, char** argv);
static void* GSQLite_Open();
static void GSQLite_Exec(void* onExec, void* params, char* sqlQuery);
//===============================================
static void GSQLite_QueryShow(char* sqlQuery, char* width, int widthD);
static void GSQLite_QueryWrite(char* sqlQuery);
static void GSQLite_QueryValue(char* sqlQuery, char* value);
static void GSQLite_QueryCol(char* sqlQuery, char* col, char* sep);
static void GSQLite_QueryRow(char* sqlQuery, char* row, char* sep);
//===============================================
static int GSQLite_OnQueryShow(void* params, int rows, char** values, char** fields);
static int GSQLite_OnQueryValue(void* params, int rows, char** values, char** fields);
static int GSQLite_OnQueryCol(void* params, int rows, char** values, char** fields);
static int GSQLite_OnQueryRow(void* params, int rows, char** values, char** fields);
//===============================================
GSQLiteO* GSQLite_New() {
	GSQLiteO* lObj = (GSQLiteO*)malloc(sizeof(GSQLiteO));

	lObj->Delete = GSQLite_Delete;
	lObj->Test = GSQLite_Test;
	lObj->QueryShow = GSQLite_QueryShow;
	lObj->QueryWrite = GSQLite_QueryWrite;
	lObj->QueryValue = GSQLite_QueryValue;
	lObj->QueryCol = GSQLite_QueryCol;
	lObj->QueryRow = GSQLite_QueryRow;
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
static void GSQLite_Test(int argc, char** argv) {
    char lSqlQuery[B_QUERY+1];
    char lValue[B_VALUE+1];

    /*sprintf(lSqlQuery, "\
    insert into CONFIG_DATA (CONFIG_KEY, CONFIG_VALUE)\
    values ('%s', '%s') \
    ", "G_MY_KEY", "MY_VALUE");
    GSQLite()->QueryWrite(lSqlQuery);*/

    sprintf(lSqlQuery, "\
    select * from CONFIG_DATA \
    limit 5 \
    ");
    GSQLite()->QueryShow(lSqlQuery, "20;30", 25);
    printf("\n");
    
    sprintf(lSqlQuery, "\
    select CONFIG_VALUE from CONFIG_DATA \
    where CONFIG_KEY = 'G_DEPOT_ROOT' \
    ");
    GSQLite()->QueryValue(lSqlQuery, lValue);
    printf("%s\n", lValue);
    printf("\n");
    
    sprintf(lSqlQuery, "\
    select CONFIG_KEY from CONFIG_DATA \
    limit 5 \
    ");
    GSQLite()->QueryCol(lSqlQuery, lValue, "|");
    printf("%s\n", lValue);
    printf("\n");
    
    sprintf(lSqlQuery, "\
    select * from CONFIG_DATA \
    where CONFIG_KEY = 'G_MY_KEY' \
    ");
    GSQLite()->QueryRow(lSqlQuery, lValue, "|");
    printf("%s\n", lValue);
    printf("\n");

    /*sprintf(lSqlQuery, "\
    delete from CONFIG_DATA\
    where CONFIG_KEY = '%s' \
    ", "G_MY_KEY");
    GSQLite()->QueryWrite(lSqlQuery);*/
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
static void GSQLite_Exec(void* onExec, void* params, char* sqlQuery) {
	sqlite3* lDb = GSQLite_Open();
    char* lError;
	int lOk = sqlite3_exec(lDb, sqlQuery, onExec, params, &lError);
	if(lOk != SQLITE_OK) {printf("[error] %s() : %s\n", __FUNCTION__, lError);}
    sqlite3_close(lDb);
}
//===============================================
static void GSQLite_QueryShow(char* sqlQuery, char* width, int widthD) {
    sGSQLiteShow lParams = {1, 1, width, widthD, 0};
    
    GSQLite_Exec(GSQLite_OnQueryShow, &lParams, sqlQuery);
    
    int lWidthC = GManager()->SplitCount(lParams.width, ";");
    char lWidthG[B_WIDTH+1];

    if(lParams.colCount > 0) printf("+-");
    for(int i = 0; i < lParams.colCount; i++) {
        int lWidth = lParams.widthD;
        if(i < lWidthC) {
            GManager()->SplitGet(lParams.width, lWidthG, ";", i);
            lWidth = atoi(lWidthG);
        }
        if(i != 0) printf("-+-");
        for(int j = 0; j < lWidth; j++) {
            printf("-");
        }
    }
    if(lParams.colCount > 0) printf("-+");
    if(lParams.colCount > 0) printf("\n");
}
//===============================================
static void GSQLite_QueryWrite(char* sqlQuery) {
    GSQLite_Exec(0, 0, sqlQuery);
}
//===============================================
static void GSQLite_QueryValue(char* sqlQuery, char* value) {
    sGSQLiteValue lParams = {value, 0, 0};
    GSQLite_Exec(GSQLite_OnQueryValue, &lParams, sqlQuery);
}
//===============================================
static void GSQLite_QueryCol(char* sqlQuery, char* col, char* sep) {
    col[0] = 0;
    sGSQLiteCol lParams = {col, sep, 0};
    GSQLite_Exec(GSQLite_OnQueryCol, &lParams, sqlQuery);
}
//===============================================
static void GSQLite_QueryRow(char* sqlQuery, char* row, char* sep) {
    row[0] = 0;
    sGSQLiteRow lParams = {row, sep, 0, 0};
    GSQLite_Exec(GSQLite_OnQueryRow, &lParams, sqlQuery);
}
//===============================================
static int GSQLite_OnQueryShow(void* params, int colCount, char** colValue, char** colName) {
	sGSQLiteShow* lParams = (sGSQLiteShow*)params;

    int lWidthC = GManager()->SplitCount(lParams->width, ";");
    char lWidthG[B_WIDTH+1];
    
    if(lParams->onHeader == 1) {
        printf("+-");
        for(int i = 0; i < colCount; i++) {
            int lWidth = lParams->widthD;
            if(i < lWidthC) {
                GManager()->SplitGet(lParams->width, lWidthG, ";", i);
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
                GManager()->SplitGet(lParams->width, lWidthG, ";", i);
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
                GManager()->SplitGet(lParams->width, lWidthG, ";", i);
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
            GManager()->SplitGet(lParams->width, lWidthG, ";", i);
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
    lParams->colCount = colCount;
	return 0; 
}
//===============================================
static int GSQLite_OnQueryValue(void* params, int colCount, char** colValue, char** colName) {
    sGSQLiteValue* lParams = (sGSQLiteValue*)params;
    if(lParams->count == lParams->index) {
        strcpy(lParams->value, colValue[0]);
    }
    lParams->count++;
    return 0;
}
//===============================================
static int GSQLite_OnQueryCol(void* params, int colCount, char** colValue, char** colName) {
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
static int GSQLite_OnQueryRow(void* params, int colCount, char** colValue, char** colName) {
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
