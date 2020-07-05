//===============================================
#ifndef _GSched_
#define _GSched_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSchedO GSchedO;
typedef struct _GMapO_GSched_GCHAR_PTR_GSCHEDPARAM_PTR GMapO_GSched_GCHAR_PTR_GSCHEDPARAM_PTR;
//===============================================
typedef enum _GSCHED_INITIALIZER {
	GSCHED_SCHED_FIFO
} GSCHED_INITIALIZER;
//===============================================
struct _GSchedO {
    void (*Delete)();
    void (*MallocSchedParam)(char* sigActionName);
    void (*InitSchedParam)(char* schedParamName, int priority);
    void (*SetScheduler)(char* schedParamName, int pid, int policy);
    void (*FreeSchedParam)(char* sigActionName);
#if defined(__unix)
	GMapO(GSched_GCHAR_PTR_GSCHEDPARAM_PTR)* m_schedParamMap;
#endif
};
//===============================================
GSchedO* GSched_New();
void GSched_Delete();
GSchedO* GSched();
//===============================================
#endif
//===============================================
