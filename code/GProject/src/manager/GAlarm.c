//===============================================
#include "GAlarm.h"
//===============================================
static GAlarmO* m_GAlarmO = 0;
//===============================================
static void GAlarm_Alarm(int sec);
static void GAlarm_Exec();
//===============================================
GAlarmO* GAlarm_New() {
    GAlarmO* lObj = (GAlarmO*)malloc(sizeof(GAlarmO));
    
    lObj->m_sec = 0;
    
    lObj->Delete = GAlarm_Delete;
    lObj->Alarm = GAlarm_Alarm;
    lObj->Exec = GAlarm_Exec;
    return lObj;
}
//===============================================
void GAlarm_Delete() {
    GAlarmO* lObj = GAlarm();
    if(lObj != 0) {
        free(lObj);
    }
    m_GAlarmO = 0;
}
//===============================================
GAlarmO* GAlarm() {
    if(m_GAlarmO == 0) {
        m_GAlarmO = GAlarm_New();
    }
    return m_GAlarmO;
}
//===============================================
static void GAlarm_Alarm(int sec) {
#if defined(__unix)
    m_GAlarmO->m_sec = sec;
	alarm(sec);
#endif
}
//===============================================
static void GAlarm_Exec() {
#if defined(__unix)
    if(m_GAlarmO->m_sec > 0) {
        alarm(m_GAlarmO->m_sec);
    }
#endif
}
//===============================================
