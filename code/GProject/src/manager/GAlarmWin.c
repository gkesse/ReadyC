//===============================================
#include "GAlarmWin.h"
#include "GMap2.h"
//===============================================
#if defined(__WIN32)
//===============================================
GDECLARE_MAP(GAlarmWin, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GAlarmWin, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef void WINAPI (*GALARM_CALLBACK)(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
//===============================================
static GAlarmO* m_GAlarmWinO = 0;
//===============================================
static void GAlarmWin_Callback(char* alarmId, void* func);
static void GAlarmWin_Timer(char* alarmId, int msec);
static void GAlarmWin_Start(char* alarmId);
static void GAlarmWin_Pause();
//===============================================
GAlarmO* GAlarmWin_New() {
    GAlarmO* lParent = GAlarm_New();
    GAlarmWinO* lChild = (GAlarmWinO*)malloc(sizeof(GAlarmWinO));
    
    lChild->m_timerMap = GMap_New(GAlarmWin, GCHAR_PTR, GVOID_PTR)();
    lChild->m_timerIdMap = GMap_New(GAlarmWin, GCHAR_PTR, GVOID_PTR)();
    lChild->m_callbackMap = GMap_New(GAlarmWin, GCHAR_PTR, GVOID_PTR)();

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Callback = GAlarmWin_Callback;
    lParent->Timer = GAlarmWin_Timer;
    lParent->Start = GAlarmWin_Start;
    lParent->Pause = GAlarmWin_Pause;
    return lParent;
}
//===============================================
void GAlarmWin_Delete() {
    GAlarm_Delete(m_GAlarmWinO);
    m_GAlarmWinO  = 0;
}
//===============================================
GAlarmO* GAlarmWin() {
    if(m_GAlarmWinO == 0) {
        m_GAlarmWinO = GAlarmWin_New();
    }
    return m_GAlarmWinO;
}
//===============================================
static void GAlarmWin_Timer(char* alarmId, int msec) {
    GAlarmWinO* lChild = m_GAlarmWinO->m_child;
    GMapO(GAlarmWin, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    lTimerMap->SetData(lTimerMap, alarmId, (void*)msec, GMap_EqualChar);
}
//===============================================
static void GAlarmWin_Callback(char* alarmId, void* func) {
    GAlarmWinO* lChild = m_GAlarmWinO->m_child;
    GMapO(GAlarmWin, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    lCallbackMap->SetData(lCallbackMap, alarmId, (void*)func, GMap_EqualChar);
}
//===============================================
static void GAlarmWin_Start(char* alarmId) {
    GAlarmWinO* lChild = m_GAlarmWinO->m_child;
    GMapO(GAlarmWin, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    GMapO(GAlarmWin, GCHAR_PTR, GVOID_PTR)* lTimerIdMap = lChild->m_timerIdMap;
    GMapO(GAlarmWin, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    int lTimer = (int)lTimerMap->GetData(lTimerMap, alarmId, GMap_EqualChar);
    GALARM_CALLBACK onFunc = (GALARM_CALLBACK)lCallbackMap->GetData(lCallbackMap, alarmId, GMap_EqualChar);
    MMRESULT lTimerId = timeSetEvent(lTimer, 1, (LPTIMECALLBACK)onFunc, 1, TIME_PERIODIC);   
    lTimerIdMap->SetData(lTimerIdMap, alarmId, (void*)lTimerId, GMap_EqualChar);
}
//===============================================
static void GAlarmWin_Pause() {
    while(1) {
        Sleep(1);
    }
}
//===============================================
#endif
//===============================================
