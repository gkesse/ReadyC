//===============================================
#ifndef _GScheduler_
#define _GScheduler_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSchedulerO GSchedulerO;
typedef struct _GSchedulerTaskO GSchedulerTaskO;
typedef void (*GSCHEDULER_TASK)(void* params);
//===============================================
struct _GSchedulerO {
    void (*Delete)();
    void (*Init)(int tickTime);
    void (*Start)();
    void (*AddTask)(GSCHEDULER_TASK task, int delay, int period, void* params);
    void (*GoToSleep)();
    int m_tickTime;
};
//===============================================
struct _GSchedulerTaskO {
	int m_runMe;
	int m_delay;
	int m_period;
    GSCHEDULER_TASK pTask;
 };
//===============================================
GSchedulerO* GScheduler_New();
void GScheduler_Delete();
GSchedulerO* GScheduler();
//===============================================
#endif
//===============================================
