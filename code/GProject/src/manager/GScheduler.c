//===============================================
#include "GScheduler.h"
#include "GConsole.h"
//===============================================
static GSchedulerO* m_GSchedulerO = 0;
//===============================================
static void GScheduler_Init(int tickTime);
static void GScheduler_AddTask(GSCHEDULER_TASK task, int delay, int period);
//===============================================
GSchedulerO* GScheduler_New() {
	GSchedulerO* lObj = (GSchedulerO*)malloc(sizeof(GSchedulerO));
	lObj->Delete = GScheduler_Delete;
	lObj->Init = GScheduler_Init;
	lObj->AddTask = GScheduler_AddTask;
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
static void GScheduler_Init(int tickTime) {
    GConsole()->Print("Je suis la fonction d'initialisation\n");
}
//===============================================
static void GScheduler_AddTask(GSCHEDULER_TASK task, int delay, int period) {
    GConsole()->Print("Je suis la fonction d'initialisation\n");
}
//===============================================
