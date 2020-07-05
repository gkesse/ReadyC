//===============================================
#ifndef _GProcessScheduler_
#define _GProcessScheduler_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSchedulerO GProcessSchedulerO;
//===============================================
struct _GProcessSchedulerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessScheduler_New();
void GProcessScheduler_Delete();
GProcessO* GProcessScheduler();
//===============================================
#endif
//===============================================
