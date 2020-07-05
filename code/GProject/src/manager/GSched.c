//===============================================
#include "GSched.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef struct sched_param* GSCHEDPARAM_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSCHEDPARAM_PTR, GSched_GCHAR_PTR_GSCHEDPARAM_PTR)
GDEFINE_MAP(GCHAR_PTR, GSCHEDPARAM_PTR, GSched_GCHAR_PTR_GSCHEDPARAM_PTR)
#endif
//===============================================
static GSchedO* m_GSchedO = 0;
//===============================================
static void GSched_MallocSchedParam(char* schedParamName);
static void GSched_InitSchedParam(char* schedParamName, int priority);
static void GSched_SetScheduler(char* schedParamName, int pid, int policy);
static void GSched_FreeSchedParam(char* schedParamName);
//===============================================
#if defined(__unix)
static int GSched_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSchedO* GSched_New() {
    GSchedO* lObj = (GSchedO*)malloc(sizeof(GSchedO));
    
#if defined(__unix)
	lObj->m_schedParamMap = GMap_New_GSched_GCHAR_PTR_GSCHEDPARAM_PTR();
#endif

    lObj->Delete = GSched_Delete;
    lObj->MallocSchedParam = GSched_MallocSchedParam;
    lObj->InitSchedParam = GSched_InitSchedParam;
    lObj->SetScheduler = GSched_SetScheduler;
    lObj->FreeSchedParam = GSched_FreeSchedParam;
    return lObj;
}
//===============================================
void GSched_Delete() {
    GSchedO* lObj = GSched();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSchedO = 0;
}
//===============================================
GSchedO* GSched() {
    if(m_GSchedO == 0) {
        m_GSchedO = GSched_New();
    }
    return m_GSchedO;
}
//===============================================
static void GSched_MallocSchedParam(char* schedParamName) {
#if defined(__unix)
	GMapO(GSched_GCHAR_PTR_GSCHEDPARAM_PTR)* lSchedParamMap = m_GSchedO->m_schedParamMap;
	struct sched_param* lSchedParam = (struct sched_param*)malloc(sizeof(struct sched_param));
	if(lSchedParam == 0) {GConsole()->Print("[ GSched ] Error GSched_MallocSchedParam\n"); exit(0);}
	lSchedParamMap->SetData(lSchedParamMap, schedParamName, lSchedParam, GSched_MapEqual);
#endif
}
//===============================================
static void GSched_InitSchedParam(char* schedParamName, int priority) {
#if defined(__unix)
	GMapO(GSched_GCHAR_PTR_GSCHEDPARAM_PTR)* lSchedParamMap = m_GSchedO->m_schedParamMap;
	struct sched_param* lSchedParam = lSchedParamMap->GetData(lSchedParamMap, schedParamName, GSched_MapEqual);
    lSchedParam->sched_priority = priority;
#endif
}
//===============================================
static void GSched_SetScheduler(char* schedParamName, int pid, int policy) {
#if defined(__unix)
	GMapO(GSched_GCHAR_PTR_GSCHEDPARAM_PTR)* lSchedParamMap = m_GSchedO->m_schedParamMap;
	struct sched_param* lSchedParam = lSchedParamMap->GetData(lSchedParamMap, schedParamName, GSched_MapEqual);
    int lRes = sched_setscheduler(pid, policy, lSchedParam);
	if(lRes == -1) {GConsole()->Print("[ GSched ] Error GSched_SetScheduler: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSched_FreeSchedParam(char* schedParamName) {
#if defined(__unix)
	GMapO(GSched_GCHAR_PTR_GSCHEDPARAM_PTR)* lSchedParamMap = m_GSchedO->m_schedParamMap;
	struct sched_param* lSchedParam = lSchedParamMap->GetData(lSchedParamMap, schedParamName, GSched_MapEqual);
    free(lSchedParam);
#endif
}
//===============================================
#if defined(__unix)
static int GSched_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
