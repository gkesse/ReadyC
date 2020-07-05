//===============================================
#include "GDebug.h"
//===============================================
typedef int (*GDEBUG_LOG)(char* buffer, int index, void* obj);
//===============================================
#if defined(__WIN32)
#define GDATA_PATH ".readydev\\readyc\\data"
#define GDEBUG_PATH "debug"
#define GDEBUG_FILE "debug.txt"
#endif
//===============================================
#if defined(__unix)
#define GDATA_PATH ".readydev/readyc/data"
#define GDEBUG_PATH "debug"
#define GDEBUG_FILE "debug.txt"
#endif
//===============================================
#define GDEBUG_BUFFER 1024
//===============================================
static GDebugO* m_GDebugO = 0;
//===============================================
static void GDebug_Write(int key, ...);
static void GDebug_Trace(int key, ...);
static void GDebug_Sep();
//===============================================
static void GDebug_Date(char* buffer);
static void GDebug_DebugFile(GDebugO* obj);
static void GDebug_Log(const char* data);
static void GDebug_SplitGet(const char* strIn, char* strOut, char* sep, int index);
static int GDebug_SplitCount(const char* strIn, char* sep);
//===============================================
#if defined(__WIN32)
static void GDebug_DebugFileWin(GDebugO* obj);
#endif
//===============================================
#if defined(__unix)
static void GDebug_DebugFileUnix(GDebugO* obj);
#endif
//===============================================
GDebugO* GDebug_New() {
    GDebugO* lObj = (GDebugO*)malloc(sizeof(GDebugO));

    GDebug_DebugFile(lObj);

    lObj->Delete = GDebug_Delete;
    lObj->Write = GDebug_Write;
    lObj->Trace = GDebug_Trace;
    lObj->Sep = GDebug_Sep;
    return lObj;
}
//===============================================
void GDebug_Delete() {
    GDebugO* lObj = GDebug();
    if(lObj != 0) {
        free(lObj);
    }
    m_GDebugO = 0;
}
//===============================================
GDebugO* GDebug() {
    if(m_GDebugO == 0) {
        m_GDebugO = GDebug_New();
    }
    return m_GDebugO;
}
//===============================================
static void GDebug_Write(int key, ...) {
    if(key == 0) return;
    char lBuffer[GDEBUG_BUFFER];
    int lIndex = 0;

    va_list lArgs;
    va_start(lArgs, key);
    while(1) {
        char* lData = va_arg(lArgs, char*);
        if(!strcmp(lData, _EOA_)) break;
        lIndex += sprintf(&lBuffer[lIndex], "%s", lData);
    }
    va_end(lArgs);
    GDebug_Log(lBuffer);
}
//===============================================
static void GDebug_Trace(int key, ...) {
    if(key == 0) return;
    char lBuffer[GDEBUG_BUFFER];
    int lIndex = 0;

    va_list lArgs;
    va_start(lArgs, key);
    while(1) {
        int lType = va_arg(lArgs, int);
        if(lType == _EOT_) break;
        if(lType == 1) {
            int lData = va_arg(lArgs, int);
            lIndex += sprintf(&lBuffer[lIndex], "%d", lData);
        }
        else if(lType == 10) {
            int lWidth = va_arg(lArgs, int);
            int lData = va_arg(lArgs, int);
            lIndex += sprintf(&lBuffer[lIndex], "%*d", lWidth, lData);
        }
        else if(lType == 2) {
            double lData = va_arg(lArgs, double);
            lIndex += sprintf(&lBuffer[lIndex], "%f", lData);
        }
        else if(lType == 20) {
            int lWidth = va_arg(lArgs, int);
            double lData = va_arg(lArgs, double);
            lIndex += sprintf(&lBuffer[lIndex], "%.*f", lWidth, lData);
        }
        else if(lType == 3) {
            char* lData = va_arg(lArgs, char*);
            lIndex += sprintf(&lBuffer[lIndex], "%s", lData);
        }
        else if(lType == 30) {
            int lWidth = va_arg(lArgs, int);
            char* lData = va_arg(lArgs, char*);
            lIndex += sprintf(&lBuffer[lIndex], "%*s", lWidth, lData);
        }
        else if(lType == 4) {
            GDEBUG_LOG onLogFunc = (GDEBUG_LOG)va_arg(lArgs, void*);
            void* lObj = va_arg(lArgs, void*);
            lIndex += onLogFunc(lBuffer, lIndex, lObj);
        }
    }
    va_end(lArgs);
    GDebug_Log(lBuffer);
}
//===============================================
static void GDebug_Log(const char* data) {
    int lCount = GDebug_SplitCount(data, "\n");
    char lData[256];
    char lFormat[256];
    char lDate[256];
    
    GDebug_Date(lDate);

    FILE* lpFile = fopen(m_GDebugO->m_debugFile, "a+");
    for(int i = 0; i < lCount; i++) {
        GDebug_SplitGet(data, lData, "\n", i);
        sprintf(lFormat, "%s | %s", lDate, lData);
        fprintf(lpFile, "%s\n", lFormat);
    }
    fclose(lpFile);
}
//===============================================
static void GDebug_SplitGet(const char* strIn, char* strOut, char* sep, int index) {
    int lPos = 0;
    int lOut = 0;
    int lCount = 0;
    int lFlag = 0;
    while(strIn[lPos] != 0) {
        if(lFlag == 0) {
            if(lCount == index) lFlag = 1;
            else lFlag = 2;
        }
        if(lFlag == 1) {
            char lChar = strIn[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) break;
            strOut[lOut] = lChar;
            lPos++; lOut++;
        }
        if(lFlag == 2) {
            char lChar = strIn[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) lCount++;
            lPos++;
            lFlag = 0;
        }
    }
    strOut[lOut] = 0;
}
//===============================================
static int GDebug_SplitCount(const char* strIn, char* sep) {
    int lPos = 0;
    int lCount = 0;
    while(strIn[lPos] != 0) {
        char lChar = strIn[lPos];
        char* lSearch = strchr(sep, lChar);
        if(lSearch != 0) lCount++;
        lPos++;
    }
    lCount += 1;
    return lCount;
}
//===============================================
static void GDebug_Sep() {
    const char* lSep = "=================================================";
    GDebug_Log(lSep);
}
//===============================================
static void GDebug_Date(char* buffer) {
    time_t lRawTime;
    time(&lRawTime);
    struct tm* lTimeInfo = localtime(&lRawTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    if(lTimeInfo->tm_isdst == 1) lHour++;
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", lDay, lMonth, lYear, lHour, lMin, lSec);
}
//===============================================
static void GDebug_DebugFile(GDebugO* obj) {
#if defined(__WIN32)
    GDebug_DebugFileWin(obj);
#else
    GDebug_DebugFileUnix(obj);
#endif
}
//===============================================
#if defined(__WIN32)
static void GDebug_DebugFileWin(GDebugO* obj) {
    char lCommand[256], lHomePath[256], lDebugPath[256];
    FILE* lpFile;
    int lBytes;
    
    sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
    lpFile = popen(lCommand, "r");
    lBytes = fread(lHomePath, 1, 255, lpFile);
    lHomePath[lBytes - 1] = 0;
    pclose(lpFile);
    
    sprintf(lDebugPath, "%s\\%s\\%s", lHomePath, GDATA_PATH, GDEBUG_PATH);
    sprintf(lCommand, "if not exist \"%s\" ( mkdir \"%s\" )", lDebugPath, lDebugPath);
    lpFile = popen(lCommand, "r");
    pclose(lpFile);

    sprintf(obj->m_debugFile, "%s\\%s", lDebugPath, GDEBUG_FILE);
}
#endif
//===============================================
#if defined(__unix)
void GDebug_DebugFileUnix(GDebugO* obj) {
    char lCommand[256], lHomePath[256], lDebugPath[256];
    FILE* lpFile;
    int lBytes;
    
    sprintf(lCommand, "%s", "echo $HOME");
    lpFile = popen(lCommand, "r");
    lBytes = fread(lHomePath, 1, 255, lpFile);
    lHomePath[lBytes - 1] = 0;
    pclose(lpFile);
    
    sprintf(lDebugPath, "%s/%s/%s", lHomePath, GDATA_PATH, GDEBUG_PATH);
    sprintf(lCommand, "if ! [ -d \"%s\" ] ; then mkdir -p \"%s\" ; fi", lDebugPath, lDebugPath);
    lpFile = popen(lCommand, "r");
    pclose(lpFile);

    sprintf(obj->m_debugFile, "%s/%s", lDebugPath, GDEBUG_FILE);
}
#endif
//===============================================
