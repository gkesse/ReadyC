//===============================================
#include "GThread2Unix.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef pthread_t* GPTHREADT_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GPTHREADT_PTR, GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)
GDEFINE_MAP(GCHAR_PTR, GPTHREADT_PTR, GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)
#endif
//===============================================
static GThread2O* m_GThread2UnixO = 0;
//===============================================
static void GThread2Unix_MallocThread(char* threadName);
static void GThread2Unix_Create(char* threadName, GTHREAD2_CALLBACK callback, void* params);
static void GThread2Unix_Join(char* threadName);
static void GThread2Unix_Exit(char* threadName);
static void GThread2Unix_FreeThread(char* threadName);
//===============================================
#if defined(__unix)
static int GThread2Unix_MapEqual(char* key1, char* key2);
#endif
//===============================================
GThread2O* GThread2Unix_New() {
	GThread2O* lParent = GThread2_New();
	GThread2UnixO* lChild = (GThread2O*)malloc(sizeof(GThread2UnixO));

	lChild->m_parent = lParent;
#if defined(__unix)
	lChild->m_threadMap = GMap_New_GThread2Unix_GCHAR_PTR_GPTHREADT_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GThread2Unix_Delete;
	lParent->MallocThread = GThread2Unix_MallocThread;
	lParent->Create = GThread2Unix_Create;
	lParent->Join = GThread2Unix_Join;
	lParent->Exit = GThread2Unix_Exit;
	lParent->FreeThread = GThread2Unix_FreeThread;
	return lParent;
}
//===============================================
void GThread2Unix_Delete() {
	GThread2UnixO* lObj = GThread2Unix();
	if(lObj != 0) {
		free(lObj);
	}
	m_GThread2UnixO = 0;
}
//===============================================
GThread2UnixO* GThread2Unix() {
	if(m_GThread2UnixO == 0) {
		m_GThread2UnixO = GThread2Unix_New();
	}
	return m_GThread2UnixO;
}
//===============================================
static void GThread2Unix_MallocThread(char* threadName) {
	GMapO(GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2UnixO->m_threadMap;
	pthread_t* lThread = (pthread_t*)malloc(sizeof(pthread_t));
	if(lThread == 0) {GConsole()->Print("[ GThread2Unix ] Error GThread2Unix_MallocThread\n");  exit(0);}
	lThreadMap->SetData(lThreadMap, threadName, lThread, GThread2Unix_MapEqual);
	printf("GThread2Unix_MallocThread : %p\n", lThread);
}
//===============================================
static void GThread2Unix_Create(char* threadName, GThread2Unix_CALLBACK callback, void* params) {
	GMapO(GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2UnixO->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2Unix_MapEqual);
	int lRes = pthread_create(lThread, 0, callback, params);
	if(lRes != 0) {GConsole()->Print("[ GThread2Unix ] Error GThread2Unix_Create\n");  exit(0);}
}
//===============================================
static void GThread2Unix_Join(char* threadName) {
	GMapO(GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2UnixO->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2Unix_MapEqual);
	int lRes = pthread_join(*lThread, 0);
	if(lRes != 0) {GConsole()->Print("[ GThread2Unix ] Error GThread2Unix_Join\n");  exit(0);}
}
//===============================================
static void GThread2Unix_Exit(char* threadName) {
	GMapO(GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2UnixO->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2Unix_MapEqual);
	pthread_exit(lThread);
}
//===============================================
static void GThread2Unix_FreeThread(char* threadName) {
	GMapO(GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2UnixO->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2Unix_MapEqual);
	free(lThread);
}
//===============================================
#if defined(__unix)
static int GThread2Unix_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
