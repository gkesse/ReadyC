//===============================================
#include "GThread2.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef pthread_t* GPTHREADT_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GPTHREADT_PTR, GThread2_GCHAR_PTR_GPTHREADT_PTR)
GDEFINE_MAP(GCHAR_PTR, GPTHREADT_PTR, GThread2_GCHAR_PTR_GPTHREADT_PTR)
#endif
//===============================================
static GThread2O* m_GThread2O = 0;
//===============================================
static void GThread2_MallocThread(char* threadName);
static void GThread2_Create(char* threadName, GTHREAD2_CALLBACK callback, void* params);
static void GThread2_Join(char* threadName);
static void GThread2_Exit(char* threadName);
static void GThread2_FreeThread(char* threadName);
//===============================================
static int GThread2_MapEqual(char* key1, char* key2);
//===============================================
GThread2O* GThread2_New() {
	GThread2O* lObj = (GThread2O*)malloc(sizeof(GThread2O));

	//lObj->m_threadMap = GMap_New_GThread2_GCHAR_PTR_GPTHREADT_PTR();

	lObj->Delete = GThread2_Delete;
	lObj->MallocThread = GThread2_MallocThread;
	lObj->Create = GThread2_Create;
	lObj->Join = GThread2_Join;
	lObj->Exit = GThread2_Exit;
	lObj->FreeThread = GThread2_FreeThread;
	return lObj;
}
//===============================================
void GThread2_Delete() {
	GThread2O* lObj = GThread2();
	if(lObj != 0) {
		free(lObj);
	}
	m_GThread2O = 0;
}
//===============================================
GThread2O* GThread2() {
	if(m_GThread2O == 0) {
		m_GThread2O = GThread2_New();
	}
	return m_GThread2O;
}
//===============================================
static void GThread2_MallocThread(char* threadName) {
	GMapO(GThread2_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2O->m_threadMap;
	pthread_t* lThread = (pthread_t*)malloc(sizeof(pthread_t));
	if(lThread == 0) {GConsole()->Print("[ GThread2 ] Error GThread2_MallocThread\n");  exit(0);}
	lThreadMap->SetData(lThreadMap, threadName, lThread, GThread2_MapEqual);
	printf("GThread2_MallocThread : %p\n", lThread);
}
//===============================================
static void GThread2_Create(char* threadName, GTHREAD2_CALLBACK callback, void* params) {
	GMapO(GThread2_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2O->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2_MapEqual);
	int lRes = pthread_create(lThread, 0, callback, params);
	if(lRes != 0) {GConsole()->Print("[ GThread2 ] Error GThread2_Create\n");  exit(0);}
}
//===============================================
static void GThread2_Join(char* threadName) {
	GMapO(GThread2_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2O->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2_MapEqual);
	int lRes = pthread_join(*lThread, 0);
	if(lRes != 0) {GConsole()->Print("[ GThread2 ] Error GThread2_Join\n");  exit(0);}
}
//===============================================
static void GThread2_Exit(char* threadName) {
	GMapO(GThread2_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2O->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2_MapEqual);
	pthread_exit(lThread);
}
//===============================================
static void GThread2_FreeThread(char* threadName) {
	GMapO(GThread2_GCHAR_PTR_GPTHREADT_PTR)* lThreadMap = m_GThread2O->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GThread2_MapEqual);
	free(lThread);
}
//===============================================
#if defined(__unix)
static int GThread2_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
