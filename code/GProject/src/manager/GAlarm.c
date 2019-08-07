//===============================================
#include "GAlarm.h"
//===============================================
static GAlarmO* m_GAlarmO = 0;
//===============================================
static void GAlarm_SetAlarm(int delay);
//===============================================
GAlarmO* GAlarm_New() {
    GAlarmO* lObj = (GAlarmO*)malloc(sizeof(GAlarmO));
    lObj->Delete = GAlarm_Delete;
    lObj->SetAlarm = GAlarm_SetAlarm;
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
static void GAlarm_SetAlarm(int delay) {
	alarm(delay);
}
//===============================================
