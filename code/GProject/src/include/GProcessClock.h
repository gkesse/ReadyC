//===============================================
#ifndef _GProcessClock_
#define _GProcessClock_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessClockO GProcessClockO;
//===============================================
struct _GProcessClockO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessClock_New();
void GProcessClock_Delete();
GProcessO* GProcessClock();
//===============================================
#endif
//===============================================
