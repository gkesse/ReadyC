//===============================================
#include "GDebug.h"
//===============================================
#if defined(__WIN32)
#define GDATA_PATH ".readydev\\readyc\\data"
#define GDEBUG_PATH "debug"
#define GDEBUG_FILE "debug.txt"
//===============================================
#elif defined(__unix)
#define GDATA_PATH ".readydev/readyc/data"
#define GDEBUG_PATH "debug"
#define GDEBUG_FILE "debug.txt"
#endif
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
static void GDebug_Line(const char* data);
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
	char lBuffer[256];
	char lDate[256];
	int lIndex = 0;
	GDebug_Date(lDate);
	lIndex += sprintf(&lBuffer[lIndex], "%s | ", lDate);
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
	char lBuffer[256];
	char lDate[256];
	int lIndex = 0;
	GDebug_Date(lDate);
	lIndex += sprintf(&lBuffer[lIndex], "%s | ", lDate);
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
	}
	va_end(lArgs);
	GDebug_Log(lBuffer);
}
//===============================================
static void GDebug_Log(const char* data) {
	FILE* lpFile = fopen(m_GDebugO->m_debugFile, "a+");
	fprintf(lpFile, "%s\n", data);
	fclose(lpFile);
}
//===============================================
static void GDebug_Line(const char* data) {
	char lBuffer[256];
	char lDate[256];
	GDebug_Date(lDate);
	sprintf(lBuffer, "%s | %s", lDate, data);
	GDebug_Log(lBuffer);
}
//===============================================
static void GDebug_Sep() {
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
