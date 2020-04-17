//===============================================
#ifndef _GClock_
#define _GClock_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GClockO GClockO;
//===============================================
struct _GClockO {
    void (*Delete)();
    long (*GetClock)();
    long (*GetClockPerSec)();
    double (*GetSecond)(long clock);
};
//===============================================
GClockO* GClock_New();
void GClock_Delete();
GClockO* GClock();
//===============================================
#endif
//===============================================
