//===============================================
#ifndef _GAlarm2_
#define _GAlarm2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GAlarm2O GAlarm2O;
//===============================================
struct _GAlarm2O {
    void* m_child;
    void (*Callback)(char* alarmId, void* func);
    void (*Timer)(char* alarmId, int msec);
    void (*Start)(char* alarmId);
    void (*Restart)(char* alarmId);
    void (*Pause)();
};
//===============================================
GAlarm2O* GAlarm2_New();
void GAlarm2_Delete(GAlarm2O* obj);
GAlarm2O* GAlarm2();
//===============================================
#endif
//===============================================
