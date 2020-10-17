//===============================================
#include "GManager.h"
#include "GManagerUnix.h"
#include "GManagerWin.h"
#include "GMap.h"
//===============================================
#define B_STRING (256)
#define B_TO_LOWER (256)
#define B_TO_UPPER (256)
#define B_TRIM (256)
#define B_SPLIT (256)
#define B_REPLACE (256)
//===============================================
// obj
static void GManager_Init(GManagerO* obj);
//===============================================
// global
static void GManager_Test(int argc, char** argv);
static void GManager_DataShow();
//===============================================
// terminal
static void GManager_Printf(const char* format, ...);
static void GManager_ReadLine(char* buffer, int size);
// string
static char* GManager_Copy(char* strIn);
static void GManager_ToUpper(char* strIn, char* strOut);
static void GManager_ToLower(char* strIn, char* strOut);
static void GManager_Trim(char* strIn, char* strOut);
static char* GManager_TrimLeft(char* strIn);
static char* GManager_TrimRight(char* strIn);
static void GManager_SplitGet(char* strIn, char* strOut, char* sep, int index);
static int GManager_SplitCount(char* strIn, char* sep);
static void GManager_Replace(char* strIn, char* strOut, char* pattern, char* replace);
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));
    
    GManager_Init(lObj);
    
    // global
    lObj->child = 0;
    lObj->Delete = GManager_Delete;
    lObj->Test = GManager_Test;
    lObj->DataShow = GManager_DataShow;
    // terminal
    lObj->Printf = GManager_Printf;
    lObj->ReadLine = GManager_ReadLine;
    // string
    lObj->Copy = GManager_Copy;
    lObj->ToUpper = GManager_ToUpper;
    lObj->ToLower = GManager_ToLower;
    lObj->Trim = GManager_Trim;
    lObj->SplitCount = GManager_SplitCount;
    lObj->SplitGet = GManager_SplitGet;
    lObj->Replace = GManager_Replace;
    return lObj;
}
//===============================================
void GManager_Delete() {
    GManagerO* lObj = GManager();
    if(lObj != 0) {
        free(lObj);
    }
}
//===============================================
GManagerO* GManager() {
#if defined(__unix)
    return GManagerUnix();
#elif defined(__WIN32)
    return GManagerWin();
#endif
    return 0;
}
//===============================================
// obj
//===============================================
static void GManager_Init(GManagerO* obj) {
    // manager
    obj->m_mgr = (sGManager*)malloc(sizeof(sGManager));
    // app
    obj->m_mgr->app = (sGApp*)malloc(sizeof(sGApp));
    strcpy(obj->m_mgr->app->app_name, "ReadyApp");
    strcpy(obj->m_mgr->app->home_path, "UNKNOWN");
    // sqlite
    obj->m_mgr->sqlite = (sGSQLite*)malloc(sizeof(sGSQLite));
    strcpy(obj->m_mgr->sqlite->db_path, "UNKNOWN");
    // json
    obj->m_mgr->json = (sGJson*)malloc(sizeof(sGJson));
    strcpy(obj->m_mgr->json->file, "UNKNOWN");
}
//===============================================
// global
//===============================================
static void GManager_Test(int argc, char** argv) {
    GManager()->DataShow();
}
//===============================================
static void GManager_DataShow() {
    int lWidth = -50;
    printf("\n");
    printf("#================================================\n");
    printf("[info] GManager()->m_mgr->app\n");
    printf("#================================================\n");
    printf("\n");
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->app->app_name", GManager()->m_mgr->app->app_name);
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->app->home_path", GManager()->m_mgr->app->home_path);
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->app->data_path", GManager()->m_mgr->app->data_path);
    printf("\n");
    printf("#================================================\n");
    printf("[info] GManager()->m_mgr->sqlite\n");
    printf("#================================================\n");
    printf("\n");
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->sqlite->db_path", GManager()->m_mgr->sqlite->db_path);
    printf("\n");
    printf("#================================================\n");
    printf("[info] GManager()->m_mgr->json\n");
    printf("#================================================\n");
    printf("\n");
    printf("[info] %*s : %s\n", lWidth, "GManager()->m_mgr->json->file", GManager()->m_mgr->json->file);
    printf("\n");
}
//===============================================
// terminal
//===============================================
static void GManager_Printf(const char* format, ...) {
    va_list lArgs;
    va_start (lArgs, format);
    vprintf (format, lArgs);
    fflush(stdout); 
    va_end (lArgs);
}
//===============================================
static void GManager_ReadLine(char* buffer, int size) {
    fflush(stdout); 
    fgets(buffer, size, stdin); 
    buffer[strlen(buffer)-1] = 0;
}
//===============================================
// string
//===============================================
static char* GManager_Copy(char* strIn) {
    int lSize = strlen(strIn);
    char* lStrOut = (char*)malloc(sizeof(char)*(lSize+1));
    strcpy(lStrOut, strIn);
    return lStrOut;
}
//===============================================
static void GManager_ToUpper(char* strIn, char* strOut) {
    char lStrIn[B_TO_UPPER+1];
    char lStrOut[B_TO_UPPER+1];
    int i = 0;    
    strcpy(lStrIn, strIn);
    while(1) {
        char lChar = lStrIn[i];
        if(lChar == 0) break;
        lStrOut[i] = toupper(lChar);
        i++;
    }    
    lStrOut[i] = 0;    
    strcpy(strOut, lStrOut);
}
//===============================================
static void GManager_ToLower(char* strIn, char* strOut) {
    char lStrIn[B_TO_LOWER+1];
    char lStrOut[B_TO_LOWER+1];
    int i = 0;
    strcpy(lStrIn, strIn);
    while(1) {
        char lChar = lStrIn[i];
        if(lChar == 0) break;
        lStrOut[i] = tolower(lChar);
        i++;
    }
    lStrOut[i] = 0;
    strcpy(strOut, lStrOut);
}
//===============================================
static void GManager_Trim(char* strIn, char* strOut) {
    char lStrIn[B_TRIM+1];
    strcpy(lStrIn, strIn);
    char* lStrOut = GManager_TrimRight(GManager_TrimLeft(lStrIn));
    strcpy(strOut, lStrOut);
}
//===============================================
static char* GManager_TrimLeft(char* strIn) {
    while(isspace(*strIn)) strIn++;
    return strIn;
}
//===============================================
static char* GManager_TrimRight(char* strIn) {
    char* lBack = strIn + strlen(strIn);
    while(isspace(*--lBack));
    *(lBack+1) = '\0';
    return strIn;
}
//===============================================
static int GManager_SplitCount(char* strIn, char* sep) {
    int lCount = 1;
    const char* lTmp = strIn;
    while((lTmp = strstr(lTmp, sep))) {
        lCount++;
        lTmp++;
    }
    return lCount;
}
//===============================================
static void GManager_SplitGet(char* strIn, char* strOut, char* sep, int index) {
    int lCount = 1;
    char lStrIn[B_SPLIT+1];
    strcpy(lStrIn, strIn);
    char* lTmp = lStrIn;
    char* lStart = lTmp;
    char* lEnd = lTmp;
    int lLast = 1;
    while((lTmp = strstr(lTmp, sep))) {
        lStart = lEnd;
        lEnd = lTmp;
        if(lCount > index) {lLast = 0; break;}
        lCount++;
        lTmp++;
    }
    
    if(lLast == 0) *lEnd = 0;
    else lStart = lEnd;
    if(index > 0) lStart++;
    strcpy(strOut, lStart);
}
//===============================================
static void GManager_Replace(char* strIn, char* strOut, char* pattern, char* replace) {
    char lStrIn[B_REPLACE+1];
    char lStrOut[B_REPLACE+1];
    char* lpStrIn = lStrIn;
    char* lpStrOut = lStrOut;
    strcpy(lStrIn, strIn);
    char* lTmp = lStrIn;
    int lLength;
    int lPattern = strlen(pattern);
    int lReplace = strlen(replace);
    while((lTmp = strstr(lTmp, pattern))) {
        lLength = lTmp - lpStrIn;
        strncpy(lpStrOut, lpStrIn, lLength); lpStrOut += lLength; *lpStrOut = 0;
        strncpy(lpStrOut, replace, lReplace); lpStrOut += lReplace; *lpStrOut = 0;
        lpStrIn += lLength + lPattern;
        lTmp++;
    }
    strcpy(lpStrOut, lpStrIn);
    strcpy(strOut, lStrOut);
}
//===============================================
