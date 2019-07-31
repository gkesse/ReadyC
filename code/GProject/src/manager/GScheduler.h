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
