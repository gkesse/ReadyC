//===============================================
#include "GThread2Unix.h"
#include "GMap2.h"
//===============================================
#if defined(__unix)
//===============================================
GDECLARE_MAP(GThread2Unix, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GThread2Unix, GCHAR_PTR, GVOID_PTR)
//===============================================
static GThread2O* m_GThread2UnixO = 0;
//===============================================
static void GThread2Unix_Create(char* threadName, void* onFunc, void* params);
static void GThread2Unix_Join(char* threadName);
static void GThread2Unix_Exit(char* threadName);
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
	lParent->Exit = GThread2Unix_Exit;
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
static void GThread2Unix_Create(char* threadName, void* onFunc, void* params) {
	GThread2UnixO* lThread2Unix = m_GThread2UnixO->m_child;
	GMapO(GThread2Unix, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Unix->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GMap_EqualChar);
	int lRes = pthread_create(lThread, 0, onFunc, params);
	if(lRes != 0) {Gprintf("[GThread2Unix] Error GThread2Unix_Create\n");  exit(0);}
}
//===============================================
static void GThread2Unix_Join(char* threadName) {
	GThread2UnixO* lThread2Unix = m_GThread2UnixO->m_child;
	GMapO(GThread2Unix, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Unix->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GMap_EqualChar);
	int lRes = pthread_join(*lThread, 0);
	if(lRes != 0) {Gprintf("[GThread2Unix] Error GThread2Unix_Join\n");  exit(0);}
}
//===============================================
static void GThread2Unix_Exit(char* threadName) {
	GThread2UnixO* lThread2Unix = m_GThread2UnixO->m_child;
	GMapO(GThread2Unix, GCHAR_PTR, GVOID_PTR)* lThreadMap = lThread2Unix->m_threadMap;
	pthread_t* lThread = lThreadMap->GetData(lThreadMap, threadName, GMap_EqualChar);
	pthread_exit(lThread);
}
//===============================================
#endif
//===============================================
