//===============================================
#include "GThread2Unix.h"
#include "GMap2.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_THREAD_ON_)
//===============================================
#if defined(__unix)
//===============================================
GDECLARE_MAP(GThread2Unix, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GThread2Unix, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef void* (*GTHREAD_FUNC)(void* params);
//===============================================
static GThread2O* m_GThread2UnixO = 0;
//===============================================
static void GThread2Unix_Create(char* threadId, void* onFunc, void* params);
static void GThread2Unix_Join(char* threadId, int delay);
static void GThread2Unix_Close(char* threadId);
//===============================================
GThread2O* GThread2Unix_New() {
	GThread2O* lParent = GThread2_New();
	GThread2UnixO* lChild = (GThread2UnixO*)malloc(sizeof(GThread2UnixO));

	lChild->m_parent = lParent;
	lChild->m_threadMap = GMap_New(GThread2Unix, GCHAR_PTR, GVOID_PTR)();

	lParent->m_child = lChild;
	lParent->Delete = GThread2Unix_Delete;
	lParent->Create = GThread2Unix_Create;
	lParent->Join = GThread2Unix_Join;
	lParent->Close = GThread2Unix_Close;
	return lParent;
}
//===============================================
void GThread2Unix_Delete(GThread2O* obj) {
	GThread2_Delete(obj);
	m_GThread2UnixO = 0;
}
//===============================================
GThread2O* GThread2Unix() {
	if(m_GThread2UnixO == 0) {
		m_GThread2UnixO = GThread2Unix_New();
	}
	return m_GThread2UnixO;
}
//===============================================
static void GThread2Unix_Create(char* threadId, void* onFunc, void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	GThread2UnixO* lThread2Unix = m_GThread2UnixO->m_child;
	GMapO(GThread2Unix, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Unix->m_threadMap;
	pthread_t* lThread = (pthread_t*)malloc(sizeof(pthread_t));
	int lRes = pthread_create(lThread, 0, (GTHREAD_FUNC)onFunc, params);
	if(lRes != 0) {printf("[GThread2Unix] Erreur creation\n");  exit(0);}
    lThreadMap->SetData(lThreadMap, threadId, lThread, GMap_EqualChar);
}
//===============================================
static void GThread2Unix_Join(char* threadId, int delay) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	GThread2UnixO* lThread2Unix = m_GThread2UnixO->m_child;
	GMapO(GThread2Unix, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Unix->m_threadMap;
	pthread_t* lThread = (pthread_t*)lThreadMap->GetData(lThreadMap, threadId, GMap_EqualChar);
	int lRes = pthread_join(*lThread, 0);
	if(lRes != 0) {printf("[GThread2Unix] Erreur synchronisation\n");  exit(0);}
}
//===============================================
static void GThread2Unix_Close(char* threadId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	GThread2UnixO* lThread2Unix = m_GThread2UnixO->m_child;
	GMapO(GThread2Unix, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Unix->m_threadMap;
	pthread_t* lThread = (pthread_t*)lThreadMap->GetData(lThreadMap, threadId, GMap_EqualChar);
	pthread_exit(lThread);
    free(lThread);
}
//===============================================
#endif
//===============================================
#endif
//===============================================
