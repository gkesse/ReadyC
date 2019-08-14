//===============================================
#ifndef _GScheduler_
#define _GScheduler_
//===============================================
#include "GInclude.h"
#include "GList.h"
//===============================================
typedef struct _GSchedulerO GSchedulerO;
typedef struct _GSchedulerTaskO GSchedulerTaskO;
typedef void (*GSCHEDULER_TASK)();
//===============================================
typedef struct _GListO_GScheduler_GSCHEDULERTASK_PTR GListO_GScheduler_GSCHEDULERTASK_PTR;
//===============================================
struct _GSchedulerO {
    void (*Delete)();
    void (*Init)(long tickTimeUsec);
    void (*Start)();
    void (*AddTask)(GSCHEDULER_TASK task, int delay, int period);
    void (*MainLoop)();
    GListO(GScheduler_GSCHEDULERTASK_PTR)* m_taskMap;
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
