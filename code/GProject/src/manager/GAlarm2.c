//===============================================
#include "GAlarm2.h"
#include "GAlarm2Win.h"
#include "GAlarm2Unix.h"
//===============================================
static void GAlarm2_Callback(char* alarmId, void* func);
static void GAlarm2_Timer(char* alarmId, int msec);
static void GAlarm2_Start(char* alarmId);
static void GAlarm2_Restart(char* alarmId);
static void GAlarm2_Pause();
//===============================================
GAlarm2O* GAlarm2_New() {
    GAlarm2O* lObj = (GAlarm2O*)malloc(sizeof(GAlarm2O));
    lObj->m_child = 0;
    lObj->Callback = GAlarm2_Callback;
    lObj->Timer = GAlarm2_Timer;
    lObj->Start = GAlarm2_Start;
    lObj->Restart = GAlarm2_Restart;
    lObj->Pause = GAlarm2_Pause;
    return lObj;
}
//===============================================
void GAlarm2_Delete(GAlarm2O* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GAlarm2O* GAlarm2() {
#if defined(__WIN32)
    return GAlarm2Win();
#elif defined(__unix)
    return GAlarm2Unix();
#endif
    return 0;
}
//===============================================
static void GAlarm2_Callback(char* alarmId, void* func) {}
static void GAlarm2_Timer(char* alarmId, int msec) {}
static void GAlarm2_Start(char* alarmId) {}
static void GAlarm2_Restart(char* alarmId) {}
static void GAlarm2_Pause() {}
//===============================================

