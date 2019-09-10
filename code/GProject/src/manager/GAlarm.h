//===============================================
#ifndef _GAlarm_
#define _GAlarm_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GAlarmO GAlarmO;
//===============================================
struct _GAlarmO {
    void (*Delete)();
    void (*Alarm)(int sec);
    void (*Exec)();
    int m_sec;
};
//===============================================
GAlarmO* GAlarm_New();
void GAlarm_Delete();
GAlarmO* GAlarm();
//===============================================
#endif
//===============================================
