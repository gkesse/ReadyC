//===============================================
#include "GDir.h"
#include "GShell.h"
#include "GDebug.h"
//===============================================
static GDirO* m_GDirO = 0;
//===============================================
static void GDir_Test(int argc, char** argv);
static char* GDir_HomePath();
static char* GDir_DataPath();
//===============================================
static void GDir_GetHomePath(char* buffer);
//===============================================
#if defined(__WIN32)
static void GDir_GetHomePathWin(char* buffer);
#endif
//===============================================
#if defined(__unix)
static void GDir_GetHomePathUnix(char* buffer);
#endif
//===============================================
GDirO* GDir_New() {
	GDebug()->Write(__FUNCTION__, 0);
	GDirO* lObj = (GDirO*)malloc(sizeof(GDirO));

	GDir_GetHomePath(lObj->m_homePath);
	sprintf(lObj->m_dataPath, "%s/%s", lObj->m_homePath, ".readydev/readyc");

	lObj->Delete = GDir_Delete;
	lObj->Test = GDir_Test;
	lObj->HomePath = GDir_HomePath;
	lObj->DataPath = GDir_DataPath;
	return lObj;
}
//===============================================
void GDir_Delete() {
	GDebug()->Write(__FUNCTION__, 0);
	GDirO* lObj = GDir();
	free(lObj);
	m_GDirO = 0;
}
//===============================================
GDirO* GDir() {
	if(m_GDirO == 0) {
		m_GDirO = GDir_New();
	}
	return m_GDirO;
}
//===============================================
static void GDir_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
	printf("%s\n", GDir()->HomePath());
	printf("%s\n", GDir()->DataPath());
}
//===============================================
static char* GDir_HomePath() {
	GDebug()->Write(__FUNCTION__, 0);
	return m_GDirO->m_homePath;
}
//===============================================
static char* GDir_DataPath() {
	GDebug()->Write(__FUNCTION__, 0);
	return m_GDirO->m_dataPath;
}
//===============================================
static void GDir_GetHomePath(char* buffer) {
	GDebug()->Write(__FUNCTION__, 0);
#if defined(__WIN32)
	GDir_GetHomePathWin(buffer);
#else
	GDir_GetHomePathUnix(buffer);
#endif
}
//===============================================
#if defined(__WIN32)
static void GDir_GetHomePathWin(char* buffer) {
	GDebug()->Write(__FUNCTION__, 0);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
	GShell()->Run(lCommand, buffer, 255, 1);
}
#endif
//===============================================
#if defined(__unix)
static void GDir_GetHomePathUnix(char* buffer) {
	GDebug()->Write(__FUNCTION__, 0);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo -n $HOME");
	GShell()->Run(lCommand, buffer, 255, 0);
}
#endif
//===============================================
