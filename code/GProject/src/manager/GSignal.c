//===============================================
#include "GSignal.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef struct sigaction* GSIGACTION_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSIGACTION_PTR, GSignal_GCHAR_PTR_GSIGACTION_PTR)
GDEFINE_MAP(GCHAR_PTR, GSIGACTION_PTR, GSignal_GCHAR_PTR_GSIGACTION_PTR)
#endif
//===============================================
static GSignalO* m_GSignalO = 0;
//===============================================
static void GSignal_MallocSigAction(char* sigActionName);
static void GSignal_InitSigAction(char* sigActionName, GSIGNAL_CALLBACK callback, int flags);
static void GSignal_SetSigAction(char* sigActionName, int signalId);
//===============================================
#if defined(__unix)
static int GSignal_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSignalO* GSignal_New() {
    GSignalO* lObj = (GSignalO*)malloc(sizeof(GSignalO));
    
#if defined(__unix)
	lObj->m_sigActionMap = GMap_New_GSignal_GCHAR_PTR_GSIGACTION_PTR();
#endif

    lObj->Delete = GSignal_Delete;
    lObj->MallocSigAction = GSignal_MallocSigAction;
    lObj->InitSigAction = GSignal_InitSigAction;
    lObj->SetSigAction = GSignal_SetSigAction;
    return lObj;
}
//===============================================
void GSignal_Delete() {
    GSignalO* lObj = GSignal();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSignalO = 0;
}
//===============================================
GSignalO* GSignal() {
    if(m_GSignalO == 0) {
        m_GSignalO = GSignal_New();
    }
    return m_GSignalO;
}
//===============================================
static void GSignal_MallocSigAction(char* sigActionName) {
#if defined(__unix)
	GMapO(GSignal_GCHAR_PTR_GSIGACTION_PTR)* lSigActionMap = m_GSignalO->m_sigActionMap;
	struct sigaction* lSigAction = (struct sigaction*)malloc(sizeof(struct sigaction));
	if(lSigAction == 0) {GConsole()->Print("[ GSignal ] Error GSignal_MallocSigAction\n"); exit(0);}
	lSigActionMap->SetData(lSigActionMap, sigActionName, lSigAction, GSignal_MapEqual);
#endif
}
//===============================================
static void GSignal_InitSigAction(char* sigActionName, GSIGNAL_CALLBACK callback, int flags) {
#if defined(__unix)
	GMapO(GSignal_GCHAR_PTR_GSIGACTION_PTR)* lSigActionMap = m_GSignalO->m_sigActionMap;
	struct sigaction* lSigAction  = lSigActionMap->GetData(lSigActionMap, sigActionName, GSignal_MapEqual);
    lSigAction->sa_handler = callback;
    lSigAction->sa_flags = flags;
#endif
}
//===============================================
static void GSignal_SetSigAction(char* sigActionName, int signalId) {
#if defined(__unix)
	GMapO(GSignal_GCHAR_PTR_GSIGACTION_PTR)* lSigActionMap = m_GSignalO->m_sigActionMap;
	struct sigaction* lSigAction  = lSigActionMap->GetData(lSigActionMap, sigActionName, GSignal_MapEqual);
    sigaction(signalId, lSigAction, 0);
#endif
}
//===============================================
#if defined(__unix)
static int GSignal_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
