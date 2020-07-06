//===============================================
#include "GThread2Win.h"
#include "GMap2.h"
//===============================================
#if defined(__WIN32)
//===============================================
GDECLARE_MAP(GThread2Win, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GThread2Win, GCHAR_PTR, GVOID_PTR)
//===============================================
static GThread2O* m_GThread2WinO = 0;
//===============================================
static void GThread2Win_BeginThread(char* threadName, void* onFunc, void* params);
static void GThread2Win_WaitForSingleObject(char* threadName, int delay);
static void GThread2Win_CloseHandle(char* threadName);
//===============================================
GThread2O* GThread2Win_New() {
	GThread2O* lParent = GThread2_New();
	GThread2WinO* lChild = (GThread2WinO*)malloc(sizeof(GThread2WinO));

	lChild->m_parent = lParent;
	lChild->m_threadMap = GMap_New(GThread2Win, GCHAR_PTR, GVOID_PTR)();

	lParent->m_child = lChild;
	lParent->Delete = GThread2Win_Delete;
	lParent->BeginThread = GThread2Win_BeginThread;
	lParent->WaitForSingleObject = GThread2Win_WaitForSingleObject;
	lParent->CloseHandle = GThread2Win_CloseHandle;
	return lParent;
}
//===============================================
void GThread2Win_Delete(GThread2O* obj) {
	GThread2_Delete(obj);
	m_GThread2WinO = 0;
}
//===============================================
GThread2O* GThread2Win() {
	if(m_GThread2WinO == 0) {
		m_GThread2WinO = GThread2Win_New();
	}
	return m_GThread2WinO;
}
//===============================================
static void GThread2Win_BeginThread(char* threadName, GTHREAD2_CREATE_CALLBACK callback, void* params) {
	GThread2WinO* lThread2Windows = m_GThread2WinO->m_child;
	GMapO(GThread2Win, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Windows->m_threadMap;
    unsigned lThreadID;
	HANDLE lThread = (HANDLE)_beginthreadex(NULL, 0, callback, params, 0, &lThreadID);
	if(lThread == 0) {GConsole()->Print("[ GThread2Win ] Error GThread2Win_BeginThread\n");  exit(0);}
	lThreadMap->SetData(lThreadMap, threadName, lThread, GMap_EqualChar);
}
//===============================================
static void GThread2Win_WaitForSingleObject(char* threadName, int delay) {
	GThread2WinO* lThread2Windows = m_GThread2WinO->m_child;
	GMapO(GThread2Win, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Windows->m_threadMap;
	HANDLE lThread = (HANDLE)lThreadMap->GetData(lThreadMap, threadName, GMap_EqualChar);
    WaitForSingleObject(lThread, GTHREAD2_INIT_DELAY(delay));
}
//===============================================
static void GThread2Win_CloseHandle(char* threadName) {
	GThread2WinO* lThread2Windows = m_GThread2WinO->m_child;
	GMapO(GThread2Win, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Windows->m_threadMap;
	HANDLE lThread = (HANDLE)lThreadMap->GetData(lThreadMap, threadName, GMap_EqualChar);
    CloseHandle(lThread);
}
//===============================================
#endif
//===============================================
