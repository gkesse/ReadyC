//===============================================
#include "GLog.h"
//===============================================
static GLogO* m_GLogO = 0;
//===============================================
static void GLog_Filename();
static void GLog_Prefix();
static void GLog_Write(char* data);
//===============================================
GLogO* GLog_New() {
    GLogO* lObj = (GLogO*)malloc(sizeof(GLogO));
    lObj->Delete = GLog_Delete;
    lObj->Write = GLog_Write;
    return lObj;
}
//===============================================
void GLog_Delete() {
    GLogO* lObj = GLog();
    if(lObj != 0) {
        free(lObj);
    }
    m_GLogO = 0;
}
//===============================================
GLogO* GLog() {
    if(m_GLogO == 0) {
        m_GLogO = GLog_New();
    }
    return m_GLogO;
}
//===============================================
static void GLog_Filename() {
    time_t lTime = time(NULL);
    struct tm lLocalTime = *localtime(&lTime);
    int lYear = lLocalTime.tm_year + 1900;
    int lMonth = lLocalTime.tm_mon + 1;
    int lDay = lLocalTime.tm_mday;
    sprintf(m_GLogO->m_filename, "log_%04d_%02d_%02d.txt", lYear, lMonth, lDay);
}
//===============================================
static void GLog_Prefix() {
    time_t lTime = time(NULL);
    struct tm lLocalTime = *localtime(&lTime);
    int lYear = lLocalTime.tm_year + 1900;
    int lMonth = lLocalTime.tm_mon + 1;
    int lDay = lLocalTime.tm_mday;
    int lHour = lLocalTime.tm_hour;
    int lMin = lLocalTime.tm_min;
    int lSec = lLocalTime.tm_sec;
    sprintf(m_GLogO->m_prefix, "%04d-%02d-%02d %02d:%02d:%02d", lYear, lMonth, lDay, lHour, lMin, lSec);
}
//===============================================
static void GLog_Write(char* data) {
    GLog_Filename();
    GLog_Prefix();
    FILE* lFile = fopen(m_GLogO->m_filename, "a+"); 
    fprintf(lFile, "%s | %s\n", m_GLogO->m_prefix, data);
    fclose(lFile);
}
//===============================================
