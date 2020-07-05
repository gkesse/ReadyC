//===============================================
#include "GAlarm.h"
#include "GAlarmWin.h"
#include "GAlarmUnix.h"
//===============================================
static void GAlarm_Callback(char* alarmId, void* func);
static void GAlarm_Timer(char* alarmId, int msec);
static void GAlarm_Start(char* alarmId);
static void GAlarm_Restart(char* alarmId);
static void GAlarm_Pause();
//===============================================
GAlarmO* GAlarm_New() {
    GAlarmO* lObj = (GAlarmO*)malloc(sizeof(GAlarmO));
    lObj->m_child = 0;
    lObj->Callback = GAlarm_Callback;
    lObj->Timer = GAlarm_Timer;
    lObj->Start = GAlarm_Start;
    lObj->Restart = GAlarm_Restart;
    lObj->Pause = GAlarm_Pause;
    return lObj;
}
//===============================================
void GAlarm_Delete(GAlarmO* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GAlarmO* GAlarm() {
#if defined(__WIN32)
    return GAlarmWin();
#elif defined(__unix)
    return GAlarmUnix();
#endif
    return 0;
}
//===============================================
static void GAlarm_Callback(char* alarmId, void* func) {}
static void GAlarm_Timer(char* alarmId, int msec) {}
static void GAlarm_Start(char* alarmId) {}
static void GAlarm_Restart(char* alarmId) {}
static void GAlarm_Pause() {}
//===============================================

