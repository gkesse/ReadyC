//===============================================
#include "GScheduler.h"
#include "GSignal.h"
#include "GAlarm.h"
#include "GPause.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef GSchedulerTaskO* GSCHEDULERTASK_PTR;
//===============================================
GDECLARE_LIST(GSCHEDULERTASK_PTR, GScheduler_GSCHEDULERTASK_PTR)
GDEFINE_LIST(GSCHEDULERTASK_PTR, GScheduler_GSCHEDULERTASK_PTR)
#endif
//===============================================
static GSchedulerO* m_GSchedulerO = 0;
//===============================================
static void GScheduler_Init(int tickTime);
static void GScheduler_Start();
static void GScheduler_AddTask(GSCHEDULER_TASK task, int delay, int period);
static void GScheduler_MainLoop();
//===============================================
static void GScheduler_Update(int signo);
static void GScheduler_DispatchTasks();
static void GScheduler_GoToSleep();
static void GScheduler_DeleteTask(int index);
//===============================================
GSchedulerO* GScheduler_New() {
	GSchedulerO* lObj = (GSchedulerO*)malloc(sizeof(GSchedulerO));
    
	lObj->m_taskMap = GList_New_GScheduler_GSCHEDULERTASK_PTR();

	lObj->Delete = GScheduler_Delete;
	lObj->Init = GScheduler_Init;
	lObj->Start = GScheduler_Start;
	lObj->AddTask = GScheduler_AddTask;
	lObj->MainLoop = GScheduler_MainLoop;
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
    GSignal()->MallocSigAction("_SCHEDULER_");
    GSignal()->MallocSigJmpBuf("_SCHEDULER_");
    GSignal()->InitSigAction("_SCHEDULER_", GScheduler_Update, 0);
    GSignal()->SigAction("_SCHEDULER_", SIGALRM);
    m_GSchedulerO->m_tickTime = tickTime;
}
//===============================================
static void GScheduler_Start() {
    GAlarm()->Alarm(m_GSchedulerO->m_tickTime);
}
//===============================================
static void GScheduler_AddTask(GSCHEDULER_TASK task, int delay, int period) {
    GListO(GScheduler_GSCHEDULERTASK_PTR)* lTaskMap = m_GSchedulerO->m_taskMap;
    GSchedulerTaskO* lTask = (GSchedulerTaskO*)malloc(sizeof(GSchedulerTaskO));
    lTask->m_runMe = 0;
    lTask->m_delay = delay;
    lTask->m_period = period;
    lTask->pTask = task;
    lTaskMap->AddData(lTaskMap, lTask);    
}
//===============================================
static void GScheduler_MainLoop() {
    while(1) {
        GScheduler_DispatchTasks();
        GScheduler_GoToSleep();
    }
}
//===============================================
static void GScheduler_Update(int signo) {
    GListO(GScheduler_GSCHEDULERTASK_PTR)* lTaskMap = m_GSchedulerO->m_taskMap;
    int lTaskCount = lTaskMap->Size(lTaskMap);
    for(int lIndex = 0; lIndex < lTaskCount; lIndex++) {
        GSchedulerTaskO* lTask = lTaskMap->GetData(lTaskMap, lIndex);
        if(lTask->m_delay == 0) {
            lTask->m_runMe += 1;
            if(lTask->m_period != 0) {
                lTask->m_delay = lTask->m_period;
            }
        }
        else {
            lTask->m_delay -= 1;
        }
    }
}
//===============================================
static void GScheduler_DispatchTasks() {
    GListO(GScheduler_GSCHEDULERTASK_PTR)* lTaskMap = m_GSchedulerO->m_taskMap;
    int lTaskCount = lTaskMap->Size(lTaskMap);
    for(int lIndex = 0; lIndex < lTaskCount; lIndex++) {
        GSchedulerTaskO* lTask = lTaskMap->GetData(lTaskMap, lIndex);
        if(lTask->m_runMe > 0) {
            lTask->pTask();
            lTask->m_runMe -= 1;
            if(lTask->m_period == 0) {
                GScheduler_DeleteTask(lIndex);    
            }
        }
    }
    
}
//===============================================
static void GScheduler_GoToSleep() {
    GPause()->Pause();
    GAlarm()->Exec();
}
//===============================================
static void GScheduler_DeleteTask(int index) {
    GListO(GScheduler_GSCHEDULERTASK_PTR)* lTaskMap = m_GSchedulerO->m_taskMap;
    lTaskMap->RemoveIndex(lTaskMap, index, 0);    
}
//===============================================
