//===============================================
#include "GDir2.h"
#include "GShell.h"
#include "GDebug.h"
//===============================================
static GDir2O* m_GDir2O = 0;
//===============================================
static void GDir2_Test(int argc, char** argv);
//===============================================
static void GDir2_GetHomePath(char* buffer);
//===============================================
#if defined(__WIN32)
static void GDir2_GetHomePathWin(char* buffer);
#endif
//===============================================
#if defined(_GARCHI_UNIX_)
static void GDir2_GetHomePathUnix(char* buffer);
#endif
//===============================================
#if defined(_GARCHI_CYGWIN_)
static void GDir2_GetHomePathCygwin(char* buffer);
#endif
//===============================================
GDir2O* GDir2_New() {
	GDebug()->Write(__FUNCTION__, _EOA_);
	GDir2O* lObj = (GDir2O*)malloc(sizeof(GDir2O));

	GDir2_GetHomePath(lObj->m_homePath);
	sprintf(lObj->m_dataPath, "%s/%s", lObj->m_homePath, ".readydev/readyc");

	lObj->Delete = GDir2_Delete;
	lObj->Test = GDir2_Test;
	return lObj;
}
//===============================================
void GDir2_Delete() {
	GDebug()->Write(__FUNCTION__, _EOA_);
	GDir2O* lObj = GDir2();
	free(lObj);
	m_GDir2O = 0;
}
//===============================================
GDir2O* GDir2() {
	if(m_GDir2O == 0) {
		m_GDir2O = GDir2_New();
	}
	return m_GDir2O;
}
//===============================================
static void GDir2_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, _EOA_);
	printf("%s\n", GDir2()->m_homePath);
	printf("%s\n", GDir2()->m_dataPath);
}
//===============================================
static void GDir2_GetHomePath(char* buffer) {
	GDebug()->Write(__FUNCTION__, _EOA_);
#if defined(__WIN32)
	GDir2_GetHomePathWin(buffer);
#elif defined(_GARCHI_UNIX_)
	GDir2_GetHomePathUnix(buffer);
#elif defined(_GARCHI_CYGWIN_)
	GDir2_GetHomePathCygwin(buffer);
#endif
}
//===============================================
#if defined(__WIN32)
static void GDir2_GetHomePathWin(char* buffer) {
	GDebug()->Write(__FUNCTION__, _EOA_);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
	GShell()->Run(lCommand, buffer, 255, 1);
}
#endif
//===============================================
#if defined(_GARCHI_UNIX_)
static void GDir2_GetHomePathUnix(char* buffer) {
	GDebug()->Write(__FUNCTION__, _EOA_);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo -n $HOME");
	GShell()->Run(lCommand, buffer, 255, 0);
}
#endif
//===============================================
#if defined(_GARCHI_UNIX_)
static void GDir2_GetHomePathUnix(char* buffer) {
	GDebug()->Write(__FUNCTION__, _EOA_);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo -n $HOME");
	GShell()->Run(lCommand, buffer, 255, 0);
}
#endif
//===============================================
#if defined(_GARCHI_CYGWIN_)
static void GDir2_GetHomePathCygwin(char* buffer) {
	GDebug()->Write(__FUNCTION__, _EOA_);
	char lCommand[256];
	sprintf(lCommand, "%s", "cygpath -w $(echo $HOME)");
	GShell()->Run(lCommand, buffer, 255, 1);
}
#endif
//===============================================
