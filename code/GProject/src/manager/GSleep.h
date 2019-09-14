//===============================================
#ifndef _GSleep_
#define _GSleep_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSleepO GSleepO;
//===============================================
struct _GSleepO {
    void (*Delete)();
    void (*Sleep)(int delay);
};
//===============================================
GSleepO* GSleep_New();
void GSleep_Delete();
GSleepO* GSleep();
//===============================================
#endif
//===============================================
