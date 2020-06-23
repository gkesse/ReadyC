//===============================================
#include "GAlarm2Unix.h"
#include "GMap2.h"
//===============================================
#if defined(__unix)
//===============================================
GDECLARE_MAP(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef void (*GALARM_CALLBACK)(int sig);
//===============================================
static GAlarm2O* m_GAlarm2UnixO = 0;
//===============================================
static void GAlarm2Unix_Callback(char* alarmId, void* func);
static void GAlarm2Unix_Timer(char* alarmId, int msec);
static void GAlarm2Unix_Start(char* alarmId);
static void GAlarm2Unix_Restart(char* alarmId);
static void GAlarm2Unix_Pause();
//===============================================
GAlarm2O* GAlarm2Unix_New() {
    GAlarm2O* lParent = GAlarm2_New();
    GAlarm2UnixO* lChild = (GAlarm2UnixO*)malloc(sizeof(GAlarm2UnixO));
    
    lChild->m_timerMap = GMap_New(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)();
    lChild->m_timerIdMap = GMap_New(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)();
    lChild->m_callbackMap = GMap_New(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)();

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Callback = GAlarm2Unix_Callback;
    lParent->Timer = GAlarm2Unix_Timer;
    lParent->Start = GAlarm2Unix_Start;
    lParent->Restart = GAlarm2Unix_Restart;
    lParent->Pause = GAlarm2Unix_Pause;
    return lParent;
}
//===============================================
void GAlarm2Unix_Delete() {
    GAlarm2_Delete(m_GAlarm2UnixO);
    m_GAlarm2UnixO  = 0;
}
//===============================================
GAlarm2O* GAlarm2Unix() {
    if(m_GAlarm2UnixO == 0) {
        m_GAlarm2UnixO = GAlarm2Unix_New();
    }
    return m_GAlarm2UnixO;
}
//===============================================
static void GAlarm2Unix_Timer(char* alarmId, int msec) {
    GAlarm2UnixO* lChild = m_GAlarm2UnixO->m_child;
    GMapO(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    lTimerMap->SetData(lTimerMap, alarmId, (void*)msec, GMap_EqualChar);
}
//===============================================
static void GAlarm2Unix_Callback(char* alarmId, void* func) {
    GAlarm2UnixO* lChild = m_GAlarm2UnixO->m_child;
    GMapO(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    lCallbackMap->SetData(lCallbackMap, alarmId, (void*)func, GMap_EqualChar);
}
//===============================================
static void GAlarm2Unix_Start(char* alarmId) {
    GAlarm2UnixO* lChild = m_GAlarm2UnixO->m_child;
    GMapO(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    GMapO(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    int lTimer = (int)lTimerMap->GetData(lTimerMap, alarmId, GMap_EqualChar);
    GALARM_CALLBACK onFunc = (GALARM_CALLBACK)lCallbackMap->GetData(lCallbackMap, alarmId, GMap_EqualChar);
    signal(SIGALRM, onFunc);
    alarm(lTimer/1000); 
}
//===============================================
static void GAlarm2Unix_Restart(char* alarmId) {
    GAlarm2UnixO* lChild = m_GAlarm2UnixO->m_child;
    GMapO(GAlarm2Unix, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    int lTimer = (int)lTimerMap->GetData(lTimerMap, alarmId, GMap_EqualChar);
    alarm(lTimer/1000);
}
//===============================================
static void GAlarm2Unix_Pause() {
    while(1) {
        pause();
    }
}
//===============================================
#endif
//===============================================
