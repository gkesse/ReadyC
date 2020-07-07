//===============================================
#include "GScheduler.h"
#include "GSignal.h"
#include "GTimer2.h"
#include "GPause.h"
#include "GConsole.h"
//===============================================
#if defined(_GUSE_SCHEDULER_ON_)
//===============================================
typedef GSchedulerTaskO* GSCHEDULERTASK_PTR;
//===============================================
GDECLARE_LIST(GSCHEDULERTASK_PTR, GScheduler_GSCHEDULERTASK_PTR)
GDEFINE_LIST(GSCHEDULERTASK_PTR, GScheduler_GSCHEDULERTASK_PTR)
//===============================================
static GSchedulerO* m_GSchedulerO = 0;
//===============================================
static void GScheduler_Init(long tickTimeUsec);
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
    
#if defined(__unix) || defined(__WIN32)
    lObj->m_taskMap = GList_New_GScheduler_GSCHEDULERTASK_PTR();
#endif

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
static void GScheduler_Init(long tickTimeUsec) {
    GSignal()->MallocSigAction("_SCHEDULER_");
    GTimer2()->MallocItimerVal("_SCHEDULER_");
    GSignal()->MallocSigJmpBuf("_SCHEDULER_");
    GSignal()->InitSigAction("_SCHEDULER_", GScheduler_Update, 0);
    GTimer2()->InitItimerVal("_SCHEDULER_", 0, tickTimeUsec);
    GSignal()->SigFillSet("_SCHEDULER_");
    GSignal()->SigDelSet("_SCHEDULER_", GSIGNAL_SIGALRM);
    GSignal()->SigDelSet("_SCHEDULER_", GSIGNAL_SIGINT);
    GSignal()->SigAction("_SCHEDULER_", GSIGNAL_SIGALRM);
}
//===============================================
static void GScheduler_Start() {
    GTimer2()->SetItimer("_SCHEDULER_", GTIMER2_ITIMER_REAL);
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
}
//===============================================
static void GScheduler_DeleteTask(int index) {
    GListO(GScheduler_GSCHEDULERTASK_PTR)* lTaskMap = m_GSchedulerO->m_taskMap;
    lTaskMap->RemoveIndex(lTaskMap, index, 0);    
}
//===============================================
#endif
//===============================================
