//===============================================
#include "GDebug.h"
//===============================================
static GDebugO* m_GDebugO = 0;
//===============================================
static void GDebug_Test(int argc, char** argv);
static void GDebug_Write(const char* key, ...);
void GDebug_Sep();
//===============================================
static void GDebug_Date(char* buffer);
static void GDebug_Log(char* data);
static void GDebug_HomePath(GDebugO* obj);
void GDebug_Sep();
void GDebug_Line(const char* data);
//===============================================
#if defined(__unix)
static void GDebug_HomePathUnix(GDebugO* obj);
#endif
//===============================================
#if defined(__WIN32)
static void GDebug_HomePathWin(GDebugO* obj);
#endif
//===============================================
GDebugO* GDebug_New() {
    GDebugO* lObj = (GDebugO*)malloc(sizeof(GDebugO));

    GDebug_HomePath(lObj);

    lObj->Delete = GDebug_Delete;
    lObj->Test = GDebug_Test;
    lObj->Write = GDebug_Write;
    lObj->Sep = GDebug_Sep;
    return lObj;
}
//===============================================
void GDebug_Delete() {

}
//===============================================
GDebugO* GDebug() {
    if(m_GDebugO == 0) {
        m_GDebugO = GDebug_New();
    }
    return m_GDebugO;
}
//===============================================
static void GDebug_Test(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    printf("%s: %s\n", "Filename", m_GDebugO->m_filename);
}
//===============================================
static void GDebug_Write(const char* key, ...) {
    if(key == 0) return;
    char lBuffer[256];
    char lDate[256];
    int lIndex = 0;
    GDebug_Date(lDate);
    lIndex += sprintf(&lBuffer[lIndex], "%s | ", lDate);
    lIndex += sprintf(&lBuffer[lIndex], "%s", key);
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
void GDebug_Sep() {
    const char* lSep = "=================================================";
    GDebug_Line(lSep);
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
static void GDebug_Log(char* data) {
    FILE* lpFile = fopen(m_GDebugO->m_filename, "a+");
    fprintf(lpFile, "%s\n", data);
    fclose(lpFile);
}
//===============================================
static void GDebug_HomePath(GDebugO* obj) {
#if defined(__unix)
    GDebug_HomePathUnix(obj);
#elif defined(__WIN32)
    GDebug_HomePathWin(obj);
#endif
}
//===============================================
void GDebug_Line(const char* data) {
    char lBuffer[512];
    char lDate[256];
    GDebug_Date(lDate);
    sprintf(lBuffer, "%s | %s", lDate, data);
    GDebug_Log(lBuffer);
}
//===============================================
#if defined(__unix)
static void GDebug_HomePathUnix(GDebugO* obj) {
    char lCommand[256];
    char lHomePath[256];
    char lDebugPath[256];
    sprintf(lCommand, "%s", "echo $HOME");
    FILE* lpFile = popen(lCommand, "r");
    int lBytes = fread(lHomePath, 1, 255, lpFile);
    lHomePath[lBytes - 1] = 0;
    pclose(lpFile);
    sprintf(lDebugPath, "%s%s", lHomePath, GDEBUG_DATA_PATH);
    sprintf(obj->m_filename, "%s%s", lDebugPath, "/debug.txt");
    sprintf(lCommand, "if ! [ -d \"%s\" ] ; then mkdir -p %s ; fi", lDebugPath, lDebugPath);
    lpFile = popen(lCommand, "r");
    pclose(lpFile);
}
#endif
//===============================================
#if defined(__WIN32)
static void GDebug_HomePathWin(GDebugO* obj) {

}
#endif
//===============================================
