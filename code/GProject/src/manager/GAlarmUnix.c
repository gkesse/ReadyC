//===============================================
#include "GAlarmUnix.h"
#include "GMap2.h"
//===============================================
#if defined(__unix)
//===============================================
GDECLARE_MAP(GAlarmUnix, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GAlarmUnix, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef void (*GALARM_CALLBACK)(int sig);
//===============================================
static GAlarmO* m_GAlarmUnixO = 0;
//===============================================
static void GAlarmUnix_Callback(char* alarmId, void* func);
static void GAlarmUnix_Timer(char* alarmId, int msec);
static void GAlarmUnix_Start(char* alarmId);
static void GAlarmUnix_Restart(char* alarmId);
static void GAlarmUnix_Pause();
//===============================================
GAlarmO* GAlarmUnix_New() {
    GAlarmO* lParent = GAlarm_New();
    GAlarmUnixO* lChild = (GAlarmUnixO*)malloc(sizeof(GAlarmUnixO));
    
    lChild->m_timerMap = GMap_New(GAlarmUnix, GCHAR_PTR, GVOID_PTR)();
    lChild->m_timerIdMap = GMap_New(GAlarmUnix, GCHAR_PTR, GVOID_PTR)();
    lChild->m_callbackMap = GMap_New(GAlarmUnix, GCHAR_PTR, GVOID_PTR)();

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Callback = GAlarmUnix_Callback;
    lParent->Timer = GAlarmUnix_Timer;
    lParent->Start = GAlarmUnix_Start;
    lParent->Restart = GAlarmUnix_Restart;
    lParent->Pause = GAlarmUnix_Pause;
    return lParent;
}
//===============================================
void GAlarmUnix_Delete() {
    GAlarm_Delete(m_GAlarmUnixO);
    m_GAlarmUnixO  = 0;
}
//===============================================
GAlarmO* GAlarmUnix() {
    if(m_GAlarmUnixO == 0) {
        m_GAlarmUnixO = GAlarmUnix_New();
    }
    return m_GAlarmUnixO;
}
//===============================================
static void GAlarmUnix_Timer(char* alarmId, int msec) {
    GAlarmUnixO* lChild = m_GAlarmUnixO->m_child;
    GMapO(GAlarmUnix, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    lTimerMap->SetData(lTimerMap, alarmId, (void*)msec, GMap_EqualChar);
}
//===============================================
static void GAlarmUnix_Callback(char* alarmId, void* func) {
    GAlarmUnixO* lChild = m_GAlarmUnixO->m_child;
    GMapO(GAlarmUnix, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    lCallbackMap->SetData(lCallbackMap, alarmId, (void*)func, GMap_EqualChar);
}
//===============================================
static void GAlarmUnix_Start(char* alarmId) {
    GAlarmUnixO* lChild = m_GAlarmUnixO->m_child;
    GMapO(GAlarmUnix, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    GMapO(GAlarmUnix, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    int lTimer = (int)lTimerMap->GetData(lTimerMap, alarmId, GMap_EqualChar);
    GALARM_CALLBACK onFunc = (GALARM_CALLBACK)lCallbackMap->GetData(lCallbackMap, alarmId, GMap_EqualChar);
    signal(SIGALRM, onFunc);
    alarm(lTimer/1000); 
}
//===============================================
static void GAlarmUnix_Restart(char* alarmId) {
    GAlarmUnixO* lChild = m_GAlarmUnixO->m_child;
    GMapO(GAlarmUnix, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    int lTimer = (int)lTimerMap->GetData(lTimerMap, alarmId, GMap_EqualChar);
    alarm(lTimer/1000);
}
//===============================================
static void GAlarmUnix_Pause() {
    while(1) {
        pause();
    }
}
//===============================================
#endif
//===============================================
