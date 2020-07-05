//===============================================
#include "GThread2Windows.h"
#include "GConsole.h"
//===============================================
#if defined(__WIN32)
typedef char* GCHAR_PTR;
typedef HANDLE GHANDLE_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GHANDLE_PTR, GThread2Windows_GCHAR_PTR_GHANDLE_PTR)
GDEFINE_MAP(GCHAR_PTR, GHANDLE_PTR, GThread2Windows_GCHAR_PTR_GHANDLE_PTR)
#endif
//===============================================
static GThread2O* m_GThread2WindowsO = 0;
//===============================================
static void GThread2Windows_BeginThread(char* threadName, GTHREAD2_CREATE_CALLBACK callback, void* params);
static void GThread2Windows_WaitForSingleObject(char* threadName, int delay);
static void GThread2Windows_CloseHandle(char* threadName);
//===============================================
#if defined(__WIN32)
static int GThread2Windows_MapEqual(char* key1, char* key2);
static DWORD GTHREAD2_INIT_DELAY(int iVal);
#endif
//===============================================
GThread2O* GThread2Windows_New() {
	GThread2O* lParent = GThread2_New();
	GThread2WindowsO* lChild = (GThread2WindowsO*)malloc(sizeof(GThread2WindowsO));

	lChild->m_parent = lParent;
#if defined(__WIN32)
	lChild->m_threadMap = GMap_New_GThread2Windows_GCHAR_PTR_GHANDLE_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GThread2Windows_Delete;
	lParent->BeginThread = GThread2Windows_BeginThread;
	lParent->WaitForSingleObject = GThread2Windows_WaitForSingleObject;
	lParent->CloseHandle = GThread2Windows_CloseHandle;
	return lParent;
}
//===============================================
void GThread2Windows_Delete(GThread2O* obj) {
	GThread2_Delete(obj);
	m_GThread2WindowsO = 0;
}
//===============================================
GThread2O* GThread2Windows() {
	if(m_GThread2WindowsO == 0) {
		m_GThread2WindowsO = GThread2Windows_New();
	}
	return m_GThread2WindowsO;
}
//===============================================
static void GThread2Windows_BeginThread(char* threadName, GTHREAD2_CREATE_CALLBACK callback, void* params) {
#if defined(__WIN32)
	GThread2WindowsO* lThread2Windows = m_GThread2WindowsO->m_child;
	GMapO(GThread2Windows_GCHAR_PTR_GHANDLE_PTR)* lThreadMap = lThread2Windows->m_threadMap;
    unsigned lThreadID;
	HANDLE lThread = (HANDLE)_beginthreadex(NULL, 0, callback, params, 0, &lThreadID);
	if(lThread == 0) {GConsole()->Print("[ GThread2Windows ] Error GThread2Windows_BeginThread\n");  exit(0);}
	lThreadMap->SetData(lThreadMap, threadName, lThread, GThread2Windows_MapEqual);
#endif
}
//===============================================
static void GThread2Windows_WaitForSingleObject(char* threadName, int delay) {
#if defined(__WIN32)
	GThread2WindowsO* lThread2Windows = m_GThread2WindowsO->m_child;
	GMapO(GThread2Windows_GCHAR_PTR_GHANDLE_PTR)* lThreadMap = lThread2Windows->m_threadMap;
	HANDLE lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2Windows_MapEqual);
    WaitForSingleObject(lThread, GTHREAD2_INIT_DELAY(delay));
#endif
}
//===============================================
static void GThread2Windows_CloseHandle(char* threadName) {
#if defined(__WIN32)
	GThread2WindowsO* lThread2Windows = m_GThread2WindowsO->m_child;
	GMapO(GThread2Windows_GCHAR_PTR_GHANDLE_PTR)* lThreadMap = lThread2Windows->m_threadMap;
	HANDLE lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2Windows_MapEqual);
    CloseHandle(lThread);
#endif
}
//===============================================
#if defined(__WIN32)
static int GThread2Windows_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
#if defined(__WIN32)
static DWORD GTHREAD2_INIT_DELAY(int iVal) {
	if(iVal == GTHREAD2_INIT_INFINITE) return INFINITE;
	return INFINITE;
}
#endif
//===============================================
