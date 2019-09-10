//===============================================
#ifndef _GProcessAlarmSignal_
#define _GProcessAlarmSignal_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessAlarmSignalO GProcessAlarmSignalO;
//===============================================
struct _GProcessAlarmSignalO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessAlarmSignal_New();
void GProcessAlarmSignal_Delete();
GProcessO* GProcessAlarmSignal();
//===============================================
#endif
//===============================================
