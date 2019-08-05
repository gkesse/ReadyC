//===============================================
#ifndef _GProcessTimerInterval_
#define _GProcessTimerInterval_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessTimerIntervalO GProcessTimerIntervalO;
//===============================================
struct _GProcessTimerIntervalO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessTimerInterval_New();
void GProcessTimerInterval_Delete();
GProcessO* GProcessTimerInterval();
//===============================================
#endif
//===============================================
