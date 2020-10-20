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
#define B_TRACE_MSG (1024)
//===============================================
GDECLARE_MAP(GManager, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GManager, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef int (*GTRACE_FUNC)(char* buffer, int index, void* obj);
//===============================================
// obj
static void GManager_Init(GManagerO* obj);
//===============================================
// global
static void GManager_Test(int argc, char** argv);
static void GManager_Main();
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
// date
static void GManager_Date(char* buffer);
// trace
static void GManager_Trace(int key, ...);
static void GManager_TraceFile(char* data);
static void GManager_TraceTerminal(char* data);
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));
    
    GManager_Init(lObj);
    
    // global
    lObj->child = 0;
    lObj->Delete = GManager_Delete;
    lObj->Test = GManager_Test;
    lObj->Main = GManager_Main;
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
    // date
    lObj->Date = GManager_Date;    
    // trace
    lObj->Trace = GManager_Trace;    
    //
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
    strcpy(obj->m_mgr->app->trace_file, "UNKNOWN");
    obj->m_mgr->app->trace_on = 1;
    obj->m_mgr->app->trace_mode = "file";
    obj->m_mgr->app->date_on = 1;
    obj->m_mgr->app->col_width = -50;
    // sqlite
    obj->m_mgr->sqlite = (sGSQLite*)malloc(sizeof(sGSQLite));
    strcpy(obj->m_mgr->sqlite->db_path, "UNKNOWN");
    // json 
    obj->m_mgr->json = (sGJson*)malloc(sizeof(sGJson));
    strcpy(obj->m_mgr->json->file, "UNKNOWN");
    // opencv
    obj->m_mgr->opencv = (sGOpenCV*)malloc(sizeof(sGOpenCV));
    strcpy(obj->m_mgr->opencv->win_title, obj->m_mgr->app->app_name);
    obj->m_mgr->opencv->win_width = 640;
    obj->m_mgr->opencv->win_height = 480;
    obj->m_mgr->opencv->bg_color = CV_RGB(20, 0, 0);
    obj->m_mgr->opencv->run_me = 1;
    obj->m_mgr->opencv->delay = 30;
    obj->m_mgr->opencv->state = "close";
    obj->m_mgr->opencv->load_img = 0;
    obj->m_mgr->opencv->ratio_img = 0;
}
//===============================================
// global
//===============================================
static void GManager_Test(int argc, char** argv) {
    GManager()->DataShow();
    GMapO(GManager, GCHAR_PTR, GVOID_PTR)* lMap = GMap_New(GManager, GCHAR_PTR, GVOID_PTR)();
    lMap->SetData(lMap, "name", "Gerard KESSE", lMap->EqualChar, 0);
}
//===============================================
static void GManager_Main() {
    GManager()->Trace(3, "#================================================", 0);
    GManager()->Trace(3, "[info] main()", 0);
    GManager()->Trace(3, "#================================================", 0);
}
//===============================================
static void GManager_DataShow() {
    int lWidth = GManager()->m_mgr->app->col_width;
    GManager()->Trace(3, "[info] GManager()->m_mgr->app", 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()-> m_mgr->app->app_name", 3, " : ", 3, GManager()->m_mgr->app->app_name, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->app->home_path", 3, " : ", 3, GManager()->m_mgr->app->home_path, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->app->data_path", 3, " : ", 3, GManager()->m_mgr->app->data_path, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->app->trace_file", 3, " : ", 3, GManager()->m_mgr->app->trace_file, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->app->trace_on", 3, " : ", 1, GManager()->m_mgr->app->trace_on, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->app->trace_mode", 3, " : ", 3, GManager()->m_mgr->app->trace_mode, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->app->date_on", 3, " : ", 1, GManager()->m_mgr->app->date_on, 0);
    GManager()->Trace(3, "", 0);
    GManager()->Trace(3, "[info] GManager()->m_mgr->sqlite", 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->sqlite->db_path", 3, " : ", 3, GManager()->m_mgr->sqlite->db_path, 0);
    GManager()->Trace(3, "", 0);
    GManager()->Trace(3, "[info] GManager()->m_mgr->json", 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->json->file", 3, " : ", 3, GManager()->m_mgr->json->file, 0);
    GManager()->Trace(3, "", 0);
    GManager()->Trace(3, "[info] GManager()->m_mgr->opencv", 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->opencv->win_width", 3, " : ", 1, GManager()->m_mgr->opencv->win_width, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->opencv->win_height", 3, " : ", 1, GManager()->m_mgr->opencv->win_height, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->opencv->load_img->width", 3, " : ", 1, GManager()->m_mgr->opencv->load_img->width, 0);
    GManager()->Trace(3, "[info] ", 30, lWidth, "GManager()->m_mgr->opencv->load_img->height", 3, " : ", 1, GManager()->m_mgr->opencv->load_img->height, 0);
    GManager()->Trace(3, "", 0);
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
// date
//===============================================
static void GManager_Date(char* buffer) {
    time_t lTime;
    time(&lTime);
    struct tm* lTimeInfo = localtime(&lTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", lDay, lMonth, lYear, lHour, lMin, lSec);
}
//===============================================
// trace
//===============================================
static void GManager_Trace(int key, ...) {
    sGApp* lApp = GManager()->m_mgr->app;
    if(lApp->trace_on == 0) return;
    char lBuffer[B_TRACE_MSG+1];
    int lIndex = 0;

    va_list lArgs;
    va_start(lArgs, key);
    int lType = key;
    while(1) {
        // off
        if(lType == 0) break;
        // int
        if(lType == 1) {
            int lData = va_arg(lArgs, int);
            lIndex += sprintf(&lBuffer[lIndex], "%d", lData);
        }
        // int - width
        else if(lType == 10) {
            int lWidth = va_arg(lArgs, int);
            int lData = va_arg(lArgs, int);
            lIndex += sprintf(&lBuffer[lIndex], "%*d", lWidth, lData);
        }
        // double 
        else if(lType == 2) {
            double lData = va_arg(lArgs, double);
            lIndex += sprintf(&lBuffer[lIndex], "%f", lData);
        }
        // double - width
        else if(lType == 20) {
            int lWidth = va_arg(lArgs, int);
            double lData = va_arg(lArgs, double);
            lIndex += sprintf(&lBuffer[lIndex], "%.*f", lWidth, lData);
        }
        // string
        else if(lType == 3) {
            char* lData = va_arg(lArgs, char*);
            lIndex += sprintf(&lBuffer[lIndex], "%s", lData);
        }
        // string - width
        else if(lType == 30) {
            int lWidth = va_arg(lArgs, int);
            char* lData = va_arg(lArgs, char*);
            lIndex += sprintf(&lBuffer[lIndex], "%*s", lWidth, lData);
        }
        // struct
        else if(lType == 4) {
            GTRACE_FUNC onLogFunc = (GTRACE_FUNC)va_arg(lArgs, void*);
            void* lObj = va_arg(lArgs, void*);
            lIndex += onLogFunc(lBuffer, lIndex, lObj);
        }
        lType = va_arg(lArgs, int);
    }
    va_end(lArgs);
    // write
    if(!strcmp(lApp->trace_mode, "file")) GManager_TraceFile(lBuffer);
    else if(!strcmp(lApp->trace_mode, "stdout")) GManager_TraceTerminal(lBuffer);
}
//===============================================
static void GManager_TraceFile(char* data) {
    sGApp* lApp = GManager()->m_mgr->app;
    int lCount = GManager_SplitCount(data, "\n");
    char lData[B_STRING+1];
    char lFormat[B_STRING+1];
    char lDate[B_STRING+1];
    
    GManager_Date(lDate);

    FILE* lpFile = fopen(lApp->trace_file , "a+");
    for(int i = 0; i < lCount; i++) {
        GManager_SplitGet(data, lData, "\n", i);
        if(lApp->date_on == 1) sprintf(lFormat, "%s | %s", lDate, lData);
        else sprintf(lFormat, "%s", lData);
        fprintf(lpFile, "%s\n", lFormat);
    }
    fclose(lpFile);
}
//===============================================
static void GManager_TraceTerminal(char* data) {
    sGApp* lApp = GManager()->m_mgr->app;
    int lCount = GManager_SplitCount(data, "\n");
    char lData[B_STRING+1];
    char lFormat[B_STRING+1];
    char lDate[B_STRING+1];
    
    GManager_Date(lDate);

    for(int i = 0; i < lCount; i++) {
        GManager_SplitGet(data, lData, "\n", i);
        if(lApp->date_on == 1) sprintf(lFormat, "%s | %s", lDate, lData);
        else sprintf(lFormat, "%s", lData);
        fprintf(stdout, "%s\n", lFormat);
    }
}
//===============================================
