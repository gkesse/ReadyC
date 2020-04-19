//===============================================
#include "GDbus.h"
#include "GShell.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_DBUS_ON_)
//===============================================
static GDbusO* m_GDbusO = 0;
//===============================================
static void GDbus_Test(int argc, char** argv);
//===============================================
static void GDbus_GetHomePath(char* buffer);
//===============================================
#if defined(__WIN32)
static void GDbus_GetHomePathWin(char* buffer);
#endif
//===============================================
#if defined(__unix)
static void GDbus_GetHomePathUnix(char* buffer);
#endif
//===============================================
GDbusO* GDbus_New() {
	GDebug()->Write(__FUNCTION__, 0);
	GDbusO* lObj = (GDbusO*)malloc(sizeof(GDbusO));

	GDbus_GetHomePath(lObj->m_homePath);
	sprintf(lObj->m_dataPath, "%s/%s", lObj->m_homePath, ".readydev/readyc");

	lObj->Delete = GDbus_Delete;
	lObj->Test = GDbus_Test;
	return lObj;
}
//===============================================
void GDbus_Delete() {
	GDebug()->Write(__FUNCTION__, 0);
	GDbusO* lObj = GDbus();
	free(lObj);
	m_GDbusO = 0;
}
//===============================================
GDbusO* GDbus() {
	if(m_GDbusO == 0) {
		m_GDbusO = GDbus_New();
	}
	return m_GDbusO;
}
//===============================================
static void GDbus_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
	DBusError lError;
	dbus_error_init(&lError);

}
//===============================================
static void GDbus_GetHomePath(char* buffer) {
	GDebug()->Write(__FUNCTION__, 0);
#if defined(__WIN32)
	GDbus_GetHomePathWin(buffer);
#else
	GDbus_GetHomePathUnix(buffer);
#endif
}
//===============================================
#if defined(__WIN32)
static void GDbus_GetHomePathWin(char* buffer) {
	GDebug()->Write(__FUNCTION__, 0);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
	GShell()->Run(lCommand, buffer, 255, 1);
}
#endif
//===============================================
#if defined(__unix)
static void GDbus_GetHomePathUnix(char* buffer) {
	GDebug()->Write(__FUNCTION__, 0);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo -n $HOME");
	GShell()->Run(lCommand, buffer, 255, 0);
}
#endif
//===============================================
#endif
//===============================================
