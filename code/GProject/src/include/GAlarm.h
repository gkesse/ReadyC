//===============================================
#ifndef _GAlarm_
#define _GAlarm_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GAlarmO GAlarmO;
//===============================================
struct _GAlarmO {
    void* m_child;
    void (*Callback)(char* alarmId, void* func);
    void (*Timer)(char* alarmId, int msec);
    void (*Start)(char* alarmId);
    void (*Restart)(char* alarmId);
    void (*Pause)();
};
//===============================================
GAlarmO* GAlarm_New();
void GAlarm_Delete(GAlarmO* obj);
GAlarmO* GAlarm();
//===============================================
#endif
//===============================================
