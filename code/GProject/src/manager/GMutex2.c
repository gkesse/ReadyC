//===============================================
#include "GMutex2.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef pthread_mutex_t* GPTHREADMUTEX_PTR;
typedef pthread_attr_t* GPTHREADATTR_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GPTHREADMUTEX_PTR, GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)
GDEFINE_MAP(GCHAR_PTR, GPTHREADMUTEX_PTR, GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GPTHREADATTR_PTR, GMutex2_GCHAR_PTR_GPTHREADATTR_PTR)
GDEFINE_MAP(GCHAR_PTR, GPTHREADATTR_PTR, GMutex2_GCHAR_PTR_GPTHREADATTR_PTR)
#endif
//===============================================
static GMutex2O* m_GMutex2O = 0;
//===============================================
static void GMutex2_MallocThreadMutex(char* threadMutexName);
static void GMutex2_InitThreadMutex(char* threadMutexName, pthread_mutex_t threadMutex);
static void GMutex2_MutexLock(char* threadMutexName);
static void GMutex2_MutexUnlock(char* threadMutexName);
static void GMutex2_FreeThreadMutex(char* threadMutexName);
//===============================================
#if defined(__unix)
static int GMutex2_MapEqual(char* key1, char* key2) ;
#endif
//===============================================
GMutex2O* GMutex2_New() {
    GMutex2O* lObj = (GMutex2O*)malloc(sizeof(GMutex2O));

#if defined(__unix)
    lObj->m_threadMutexMap = GMap_New_GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR();
    lObj->m_threadAttrMap = GMap_New_GMutex2_GCHAR_PTR_GPTHREADATTR_PTR();
#endif

    lObj->Delete = GMutex2_Delete;
    lObj->MallocThreadMutex = GMutex2_MallocThreadMutex;
    lObj->InitThreadMutex = GMutex2_InitThreadMutex;
    lObj->MutexLock = GMutex2_MutexLock;
    lObj->MutexUnlock = GMutex2_MutexUnlock;
    lObj->FreeThreadMutex = GMutex2_FreeThreadMutex;
    return lObj;
}
//===============================================
void GMutex2_Delete() {
    GMutex2O* lObj = GMutex2();
    if(lObj != 0) {
        free(lObj);
    }
    m_GMutex2O = 0;
}
//===============================================
GMutex2O* GMutex2() {
    if(m_GMutex2O == 0) {
        m_GMutex2O = GMutex2_New();
    }
    return m_GMutex2O;
}
//===============================================
static void GMutex2_MallocThreadMutex(char* threadMutexName) {
	GMapO(GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)* lThreadMutexMap = m_GMutex2O->m_threadMutexMap;
	pthread_mutex_t* lThreadMutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	if(lThreadMutex == 0) {GConsole()->Print("[ GMutex2 ] Error GMutex2_MallocThreadMutex\n"); exit(0);}
	lThreadMutexMap->SetData(lThreadMutexMap, threadMutexName, lThreadMutex, GMutex2_MapEqual);
}
//===============================================
static void GMutex2_InitThreadMutex(char* threadMutexName, pthread_mutex_t threadMutex) {
	GMapO(GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)* lThreadMutexMap = m_GMutex2O->m_threadMutexMap;
	pthread_mutex_t* lThreadMutex = lThreadMutexMap->GetData(lThreadMutexMap, threadMutexName, GMutex2_MapEqual);
	*lThreadMutex = threadMutex;
}
//===============================================
static void GMutex2_MutexLock(char* threadMutexName) {
	GMapO(GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)* lThreadMutexMap = m_GMutex2O->m_threadMutexMap;
	pthread_mutex_t* lThreadMutex = lThreadMutexMap->GetData(lThreadMutexMap, threadMutexName, GMutex2_MapEqual);
	pthread_mutex_lock(lThreadMutex);
}
//===============================================
static void GMutex2_MutexUnlock(char* threadMutexName) {
	GMapO(GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)* lThreadMutexMap = m_GMutex2O->m_threadMutexMap;
	pthread_mutex_t* lThreadMutex = lThreadMutexMap->GetData(lThreadMutexMap, threadMutexName, GMutex2_MapEqual);
	pthread_mutex_unlock(lThreadMutex);
}
//===============================================
static void GMutex2_FreeThreadMutex(char* threadMutexName) {
	GMapO(GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)* lThreadMutexMap = m_GMutex2O->m_threadMutexMap;
	pthread_mutex_t* lThreadMutex = lThreadMutexMap->GetData(lThreadMutexMap, threadMutexName, GMutex2_MapEqual);
	free(lThreadMutex);
}
//===============================================
#if defined(__unix)
static int GMutex2_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
