//===============================================
#include "GAlarm2Win.h"
#include "GMap2.h"
//===============================================
#if defined(__WIN32)
//===============================================
GDECLARE_MAP(GAlarm2Win, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GAlarm2Win, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef void WINAPI (*GALARM_CALLBACK)(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
//===============================================
static GAlarm2O* m_GAlarm2WinO = 0;
//===============================================
static void GAlarm2Win_Callback(char* alarmId, void* func);
static void GAlarm2Win_Timer(char* alarmId, int msec);
static void GAlarm2Win_Start(char* alarmId);
static void GAlarm2Win_Pause();
//===============================================
GAlarm2O* GAlarm2Win_New() {
    GAlarm2O* lParent = GAlarm2_New();
    GAlarm2WinO* lChild = (GAlarm2WinO*)malloc(sizeof(GAlarm2WinO));
    
    lChild->m_timerMap = GMap_New(GAlarm2Win, GCHAR_PTR, GVOID_PTR)();
    lChild->m_timerIdMap = GMap_New(GAlarm2Win, GCHAR_PTR, GVOID_PTR)();
    lChild->m_callbackMap = GMap_New(GAlarm2Win, GCHAR_PTR, GVOID_PTR)();

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Callback = GAlarm2Win_Callback;
    lParent->Timer = GAlarm2Win_Timer;
    lParent->Start = GAlarm2Win_Start;
    lParent->Pause = GAlarm2Win_Pause;
    return lParent;
}
//===============================================
void GAlarm2Win_Delete() {
    GAlarm2_Delete(m_GAlarm2WinO);
    m_GAlarm2WinO  = 0;
}
//===============================================
GAlarm2O* GAlarm2Win() {
    if(m_GAlarm2WinO == 0) {
        m_GAlarm2WinO = GAlarm2Win_New();
    }
    return m_GAlarm2WinO;
}
//===============================================
static void GAlarm2Win_Timer(char* alarmId, int msec) {
    GAlarm2WinO* lChild = m_GAlarm2WinO->m_child;
    GMapO(GAlarm2Win, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    lTimerMap->SetData(lTimerMap, alarmId, (void*)msec, GMap_EqualChar);
}
//===============================================
static void GAlarm2Win_Callback(char* alarmId, void* func) {
    GAlarm2WinO* lChild = m_GAlarm2WinO->m_child;
    GMapO(GAlarm2Win, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    lCallbackMap->SetData(lCallbackMap, alarmId, (void*)func, GMap_EqualChar);
}
//===============================================
static void GAlarm2Win_Start(char* alarmId) {
    GAlarm2WinO* lChild = m_GAlarm2WinO->m_child;
    GMapO(GAlarm2Win, GCHAR_PTR, GVOID_PTR)* lTimerMap = lChild->m_timerMap;
    GMapO(GAlarm2Win, GCHAR_PTR, GVOID_PTR)* lTimerIdMap = lChild->m_timerIdMap;
    GMapO(GAlarm2Win, GCHAR_PTR, GVOID_PTR)* lCallbackMap = lChild->m_callbackMap;
    int lTimer = (int)lTimerMap->GetData(lTimerMap, alarmId, GMap_EqualChar);
    GALARM_CALLBACK onFunc = (GALARM_CALLBACK)lCallbackMap->GetData(lCallbackMap, alarmId, GMap_EqualChar);
    MMRESULT lTimerId = timeSetEvent(lTimer, 1, (LPTIMECALLBACK)onFunc, 1, TIME_PERIODIC);   
    lTimerIdMap->SetData(lTimerIdMap, alarmId, (void*)lTimerId, GMap_EqualChar);
}
//===============================================
static void GAlarm2Win_Pause() {
    while(1) {
        Sleep(1);
    }
}
//===============================================
#endif
//===============================================
