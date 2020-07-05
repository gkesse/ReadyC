//===============================================
#include "GSemaphore.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
//===============================================
typedef char* GCHAR_PTR;
typedef sem_t* GSEM_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSEM_PTR, GSemaphore_GCHAR_PTR_GSEM_PTR)
GDEFINE_MAP(GCHAR_PTR, GSEM_PTR, GSemaphore_GCHAR_PTR_GSEM_PTR)
#endif
//===============================================
static GSemaphoreO* m_GSemaphoreO = 0;
//===============================================
static void GSemaphore_MallocSem(char* semName);
static void GSemaphore_SemOpen(char* semName, char* name, int oflag, int mode, int value);
static void GSemaphore_SemWait(char* semName);
static void GSemaphore_SemPost(char* semName);
static void GSemaphore_FreeSem(char* semName);
//===============================================
#if defined(__unix)
static int GSemaphore_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSemaphoreO* GSemaphore_New() {
    GSemaphoreO* lObj = (GSemaphoreO*)malloc(sizeof(GSemaphoreO));
    lObj->Delete = GSemaphore_Delete;
    lObj->MallocSem = GSemaphore_MallocSem;
    lObj->SemOpen = GSemaphore_SemOpen;
    lObj->SemWait = GSemaphore_SemWait;
    lObj->SemPost = GSemaphore_SemPost;
    lObj->FreeSem = GSemaphore_FreeSem;
    return lObj;
}
//===============================================
void GSemaphore_Delete() {
    GSemaphoreO* lObj = GSemaphore();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSemaphoreO = 0;
}
//===============================================
GSemaphoreO* GSemaphore() {
    if(m_GSemaphoreO == 0) {
        m_GSemaphoreO = GSemaphore_New();
    }
    return m_GSemaphoreO;
}
//===============================================
static void GSemaphore_MallocSem(char* semName) {
#if defined(__unix)
	GMapO(GSemaphore_GCHAR_PTR_GSEM_PTR)* lSemMap = m_GSemaphoreO->m_semMap;
	sem_t* lSem = (sem_t*)malloc(sizeof(sem_t));
	if(lSem == 0) {GConsole()->Print("[ GMutex2 ] Error GSemaphore_MallocSem\n"); exit(0);}
	lSemMap->SetData(lSemMap, semName, lSem, GSemaphore_MapEqual);
#endif
}
//===============================================
static void GSemaphore_SemOpen(char* semName, char* name, int oflag, int mode, int value) {
#if defined(__unix)
	GMapO(GSemaphore_GCHAR_PTR_GSEM_PTR)* lSemMap = m_GSemaphoreO->m_semMap;
	sem_t* lSem = sem_open(name, oflag, mode, value);
	if(lSem == SEM_FAILED) {GConsole()->Print("[ GMutex2 ] Error GSemaphore_SemOpen\n"); exit(0);}
	lSemMap->SetData(lSemMap, semName, lSem, GSemaphore_MapEqual);
#endif
}
//===============================================
static void GSemaphore_SemWait(char* semName) {
#if defined(__unix)
	GMapO(GSemaphore_GCHAR_PTR_GSEM_PTR)* lSemMap = m_GSemaphoreO->m_semMap;
	sem_t* lSem = lSemMap->GetData(lSemMap, semName, GSemaphore_MapEqual);
	sem_wait(lSem);
#endif
}
//===============================================
static void GSemaphore_SemPost(char* semName) {
#if defined(__unix)
	GMapO(GSemaphore_GCHAR_PTR_GSEM_PTR)* lSemMap = m_GSemaphoreO->m_semMap;
	sem_t* lSem = lSemMap->GetData(lSemMap, semName, GSemaphore_MapEqual);
	sem_post(lSem);
#endif
}
//===============================================
static void GSemaphore_FreeSem(char* semName) {
#if defined(__unix)
	GMapO(GSemaphore_GCHAR_PTR_GSEM_PTR)* lSemMap = m_GSemaphoreO->m_semMap;
	sem_t* lSem = lSemMap->GetData(lSemMap, semName, GSemaphore_MapEqual);
	free(lSem);
#endif
}
//===============================================
#if defined(__unix)
static int GSemaphore_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
