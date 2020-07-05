//===============================================
#ifndef _GProcessRaceCondition_
#define _GProcessRaceCondition_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessRaceConditionO GProcessRaceConditionO;
//===============================================
struct _GProcessRaceConditionO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessRaceCondition_New();
void GProcessRaceCondition_Delete();
GProcessO* GProcessRaceCondition();
//===============================================
#endif
//===============================================
