//===============================================
#include "GThread2Win.h"
#include "GMap2.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_THREAD_ON_)
//===============================================
#if defined(__WIN32)
//===============================================
GDECLARE_MAP(GThread2Win, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GThread2Win, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef unsigned __stdcall (*GTHREAD_FUNC)(void* params);
//===============================================
static GThread2O* m_GThread2WinO = 0;
//===============================================
static void GThread2Win_Create(char* threadId, void* onFunc, void* params);
static void GThread2Win_Join(char* threadId, int delay);
static void GThread2Win_Close(char* threadId);
//===============================================
GThread2O* GThread2Win_New() {
	GThread2O* lParent = GThread2_New();
	GThread2WinO* lChild = (GThread2WinO*)malloc(sizeof(GThread2WinO));

	lChild->m_parent = lParent;
	lChild->m_threadMap = GMap_New(GThread2Win, GCHAR_PTR, GVOID_PTR)();

	lParent->m_child = lChild;
	lParent->Delete = GThread2Win_Delete;
	lParent->Create = GThread2Win_Create;
	lParent->Join = GThread2Win_Join;
	lParent->Close = GThread2Win_Close;
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
static void GThread2Win_Create(char* threadId, void* onFunc, void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	GThread2WinO* lThread2Windows = m_GThread2WinO->m_child;
	GMapO(GThread2Win, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Windows->m_threadMap;
    unsigned lThreadID;
	HANDLE lThread = (HANDLE)_beginthreadex(NULL, 0, (GTHREAD_FUNC)onFunc, params, 0, &lThreadID);
	if(lThread == 0) {printf("[GThread2Win] Erreur demarrage\n");  exit(0);}
	lThreadMap->SetData(lThreadMap, threadId, (void*)lThread, GMap_EqualChar);
}
//===============================================
static void GThread2Win_Join(char* threadId, int delay) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	GThread2WinO* lThread2Windows = m_GThread2WinO->m_child;
	GMapO(GThread2Win, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Windows->m_threadMap;
	HANDLE lThread = (HANDLE)lThreadMap->GetData(lThreadMap, threadId, GMap_EqualChar);
    WaitForSingleObject(lThread, (DWORD)delay);
}
//===============================================
static void GThread2Win_Close(char* threadId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	GThread2WinO* lThread2Windows = m_GThread2WinO->m_child;
	GMapO(GThread2Win, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Windows->m_threadMap;
	HANDLE lThread = (HANDLE)lThreadMap->GetData(lThreadMap, threadId, GMap_EqualChar);
    CloseHandle(lThread);
}
//===============================================
#endif
//===============================================
#endif
//===============================================
