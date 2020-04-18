//===============================================
#include "GDebug.h"
//===============================================
static GDebugO* m_GDebugO = 0;
//===============================================
#define _GDEBUG_CLEAR_OFF_
//===============================================
static void GDebug_Test(int argc, char** argv);
static void GDebug_Write(const char* key, ...);
static void GDebug_Clear();
static void GDebug_Sep();
//===============================================
static void GDebug_Date(char* buffer);
static void GDebug_HomePath(GDebugO* obj);
static void GDebug_Log(const char* data);
static void GDebug_Line(const char* data);
static void GDebug_ClearObj(GDebugO* obj);
//===============================================
#if defined(__WIN32)
static void GDebug_HomePathWin(GDebugO* obj);
#endif
//===============================================
#if defined(__unix)
static void GDebug_HomePathUnix(GDebugO* obj);
#endif
//===============================================
GDebugO* GDebug_New() {
	GDebugO* lObj = (GDebugO*)malloc(sizeof(GDebugO));

	GDebug_HomePath(lObj);
	GDebug_ClearObj(lObj);

	lObj->Delete = GDebug_Delete;
	lObj->Test = GDebug_Test;
	lObj->Write = GDebug_Write;
	lObj->Clear = GDebug_Clear;
	lObj->Sep = GDebug_Sep;
	return lObj;
}
//===============================================
void GDebug_Delete() {
	GDebugO* lObj = GDebug();
	free(lObj);
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
static void GDebug_Test(int argc, char** argv) {
	printf("%s\n", GDebug()->m_homePath);
	printf("%s\n", GDebug()->m_debugPath);
	printf("%s\n", GDebug()->m_filename);
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
		if(lData == 0) break;
		lIndex += sprintf(&lBuffer[lIndex], "%s", lData);
	}
	va_end(lArgs);
	GDebug_Log(lBuffer);
}
//===============================================
static void GDebug_Log(const char* data) {
	FILE* lpFile = fopen(m_GDebugO->m_filename, "a+");
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
static void GDebug_Clear() {
	FILE* lpFile = fopen(m_GDebugO->m_filename, "w");
	fclose(lpFile);
}
//===============================================
static void GDebug_ClearObj(GDebugO* obj) {
#if defined(_GDEBUG_CLEAR_ON_)
	FILE* lpFile = fopen(obj->m_filename, "w");
	fclose(lpFile);
#endif
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
static void GDebug_HomePath(GDebugO* obj) {
#if defined(__WIN32)
	GDebug_HomePathWin(obj);
#else
	GDebug_HomePathUnix(obj);
#endif
}
//===============================================
#if defined(__WIN32)
static void GDebug_HomePathWin(GDebugO* obj) {
	char lCommand[256];
	sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
	FILE* lpFile = popen(lCommand, "r");
	int lBytes = fread(obj->m_homePath, 1, 255, lpFile);
	obj->m_homePath[lBytes - 1] = 0;
	pclose(lpFile);
	sprintf(obj->m_debugPath, "%s\\%s", obj->m_homePath, ".readydev\\readyc\\data\\debug");
	sprintf(obj->m_filename, "%s\\%s", obj->m_debugPath, "debug.txt");
	sprintf(lCommand, "if not exist %s ( mkdir %s )", obj->m_debugPath, obj->m_debugPath);
	lpFile = popen(lCommand, "r");
	pclose(lpFile);
}
#endif
//===============================================
#if defined(__unix)
void GDebug_HomePathUnix(GDebugO* obj) {
	char lCommand[256];
	sprintf(lCommand, "%s", "echo -n $HOME");
	FILE* lpFile = popen(lCommand, "r");
	int lBytes = fread(obj->m_homePath, 1, 255, lpFile);
	m_homePath[lBytes] = 0;
	pclose(lpFile);
	sprintf(obj->m_debugPath, "%s/%s", obj->m_homePath, ".readydev/readycpp/data/debug");
	sprintf(obj->m_filename, "%s/%s", obj->m_debugPath, "debug.txt");
	sprintf(lCommand, "if [ -d \"%s\" ] ; then mkdir -p %s ; fi", obj->m_debugPath, obj->m_debugPath);
	lpFile = popen(lCommand, "r");
	pclose(lpFile);
}
#endif
//===============================================