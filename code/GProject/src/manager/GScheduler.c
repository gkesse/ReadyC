//===============================================
#include "GScheduler.h"
#include "GConsole.h"
///===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef pthread_t* GPTHREADT_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GPTHREADT_PTR, GScheduler_GCHAR_PTR_GPTHREADT_PTR)
GDEFINE_MAP(GCHAR_PTR, GPTHREADT_PTR, GScheduler_GCHAR_PTR_GPTHREADT_PTR)
#endif
//===============================================
static GSchedulerO* m_GSchedulerO = 0;
//===============================================
#if defined(__unix)
static int GScheduler_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSchedulerO* GScheduler_New() {
	GSchedulerO* lObj = (GSchedulerO*)malloc(sizeof(GSchedulerO));

	//lObj->m_threadMap = GMap_New_GScheduler_GCHAR_PTR_GPTHREADT_PTR();

	lObj->Delete = GScheduler_Delete;
	return lObj;
}
//===============================================
void GScheduler_Delete() {
	GSchedulerO* lObj = GScheduler();
	if(lObj != 0) {
		free(lObj);
	}
	m_GSchedulerO = 0;
}
//===============================================
GSchedulerO* GScheduler() {
	if(m_GSchedulerO == 0) {
		m_GSchedulerO = GScheduler_New();
	}
	return m_GSchedulerO;
}
//===============================================
static void GScheduler_AddTask(GSCHEDULER_TASK task, int delay, int period) {

}
//===============================================
#if defined(__unix)
static int GScheduler_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
