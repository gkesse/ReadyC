//===============================================
#include "GScheduler.h"
#include "GSignal.h"
#include "GAlarm.h"
#include "GMainLoop2.h"
#include "GConsole.h"
//===============================================
static GSchedulerO* m_GSchedulerO = 0;
//===============================================
static void GScheduler_Init(int tickTime);
static void GScheduler_Start();
static void GScheduler_AddTask(GSCHEDULER_TASK task, int delay, int period, void* params);
static void GScheduler_GoToSleep();
//===============================================
static void GScheduler_Update(int signo);
//===============================================
GSchedulerO* GScheduler_New() {
	GSchedulerO* lObj = (GSchedulerO*)malloc(sizeof(GSchedulerO));
	lObj->Delete = GScheduler_Delete;
	lObj->Init = GScheduler_Init;
	lObj->Start = GScheduler_Start;
	lObj->AddTask = GScheduler_AddTask;
	lObj->GoToSleep = GScheduler_GoToSleep;
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
    GSignal()->MallocSigAction("SCHEDULER");
    GSignal()->MallocSigJmpBuf("SCHEDULER");
    GSignal()->InitSigAction("SCHEDULER", GScheduler_Update, 0);
    GSignal()->SigAction("SCHEDULER", SIGALRM);
    m_GSchedulerO->m_tickTime = tickTime;
}
//===============================================
static void GScheduler_Start() {
    GConsole()->Print("Je suis la fonction d'initialisation\n");
    GAlarm()->Alarm(m_GSchedulerO->m_tickTime);
}
//===============================================
static void GScheduler_AddTask(GSCHEDULER_TASK task, int delay, int period, void* params) {
    GConsole()->Print("Je suis la fonction d'initialisation\n");
}
//===============================================
static void GScheduler_GoToSleep() {
    GConsole()->Print("Je passe en mode IDLE\n");
    GMainLoop2()->Exec();
}
//===============================================
static void GScheduler_Update(int signo) {
    GConsole()->Print("Je suis la fonction de mise a jour\n");
}
//===============================================
