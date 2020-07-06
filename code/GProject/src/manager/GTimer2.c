//===============================================
#include "GTimer2.h"
#include "GMap2.h"
//===============================================
GDECLARE_MAP(GTimer2, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GTimer2, GCHAR_PTR, GVOID_PTR)
//===============================================
typedef void (*GTIMER2_FUNC)(int params);
//===============================================
static GTimer2O* m_GTimer2O = 0;
//===============================================
static void GTimer2_Timer(char* timerName, char* sigEventName, int clockId);
static void GTimer2_SetTime(char* timerName, char* itimerSpecName);
static void GTimer2_Signal(char* sigEventName, int notify, int signo, void* onFunc);
static void GTimer2_Itimer(char* itimerSpecName, long sec, long nsec);
static void GTimer2_InitItimerVal(char* itimerValName, long sec, long usec);
static void GTimer2_SetItimer(char* itimerValName, int timerId);
//===============================================
GTimer2O* GTimer2_New() {
    GTimer2O* lObj = (GTimer2O*)malloc(sizeof(GTimer2O));
    
	lObj->m_timerMap = GMap_New(GTimer2, GCHAR_PTR, GVOID_PTR)();
	lObj->m_sigEventMap = GMap_New(GTimer2, GCHAR_PTR, GVOID_PTR)();
	lObj->m_itimerSpecMap = GMap_New(GTimer2, GCHAR_PTR, GVOID_PTR)();
	lObj->m_itimerValMap = GMap_New(GTimer2, GCHAR_PTR, GVOID_PTR)();
    
    lObj->Delete = GTimer2_Delete;
    lObj->Timer = GTimer2_Timer;
    lObj->SetTime = GTimer2_SetTime;
    lObj->Signal = GTimer2_Signal;
    lObj->Itimer = GTimer2_Itimer;
    lObj->Itimer = GTimer2_Itimer;
    lObj->InitItimerVal = GTimer2_InitItimerVal;
    lObj->SetItimer = GTimer2_SetItimer;
    return lObj;
}
//===============================================
void GTimer2_Delete() {
    GTimer2O* lObj = GTimer2();
    if(lObj != 0) {
        free(lObj);
    }
    m_GTimer2O = 0;
}
//===============================================
GTimer2O* GTimer2() {
    if(m_GTimer2O == 0) {
        m_GTimer2O = GTimer2_New();
    }
    return m_GTimer2O;
}
//===============================================
static void GTimer2_Timer(char* timerName, char* sigEventName, int clockId) {
	GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
	GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lSigEventMap = m_GTimer2O->m_sigEventMap;
	timer_t* lTimer = lTimerMap->GetData(lTimerMap, timerName, GMap_EqualChar);
	struct sigevent* lSignal = lSigEventMap->GetData(lSigEventMap, sigEventName, GMap_EqualChar);
	int lRes = timer_create(clockId, lSignal, lTimer);
    if(lRes != 0) {printf("[GTimer2] Error GTimer2_Timer\n"); exit(0);}
}
//===============================================
static void GTimer2_SetTime(char* timerName, char* itimerSpecName) {
	GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
    GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lItimerSpecMap = m_GTimer2O->m_itimerSpecMap;
	timer_t* lTimer = lTimerMap->GetData(lTimerMap, timerName, GMap_EqualChar);
	struct itimerspec* lItimerSpec = lItimerSpecMap->GetData(lItimerSpecMap, itimerSpecName, GMap_EqualChar);
	int lRes = timer_settime(*lTimer, 0, lItimerSpec, 0);
    if(lRes != 0) {printf("[GTimer2] Error GTimer2_SetTime\n"); exit(0);}
}
//===============================================
static void GTimer2_Signal(char* sigEventName, int notify, int signo, void* onFunc) {
	GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lSigEventMap = m_GTimer2O->m_sigEventMap;
	struct sigevent* lSignal = lSigEventMap->GetData(lSigEventMap, sigEventName, GMap_EqualChar);
	lSignal->sigev_notify = notify;
	lSignal->sigev_signo  = signo;
	signal(signo, onFunc);
}
//===============================================
static void GTimer2_Itimer(char* itimerSpecName, long sec, long nsec) {
	GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lItimerSpecMap = m_GTimer2O->m_itimerSpecMap;
	struct itimerspec* lItimerSpec = lItimerSpecMap->GetData(lItimerSpecMap, itimerSpecName, GMap_EqualChar);
	lItimerSpec->it_value.tv_sec = sec;
	lItimerSpec->it_value.tv_nsec = nsec;
	lItimerSpec->it_interval.tv_sec = sec;
	lItimerSpec->it_interval.tv_nsec = nsec;
}
//===============================================
static void GTimer2_InitItimerVal(char* itimerValName, long sec, long usec) {
	GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lItimerValMap = m_GTimer2O->m_itimerValMap;
	struct itimerval* lItimerVal = lItimerValMap->GetData(lItimerValMap, itimerValName, GMap_EqualChar);
	lItimerVal->it_value.tv_sec = sec;
	lItimerVal->it_value.tv_usec = usec;
	lItimerVal->it_interval.tv_sec = sec;
	lItimerVal->it_interval.tv_usec = usec;
}
//===============================================
static void GTimer2_SetItimer(char* itimerValName, int timerId) {
	GMapO(GTimer2, GCHAR_PTR, GVOID_PTR)* lItimerValMap = m_GTimer2O->m_itimerValMap;
	struct itimerval* lItimerVal = lItimerValMap->GetData(lItimerValMap, itimerValName, GMap_EqualChar);
    int lRes = setitimer(GTimer2_InitTimerID(timerId), lItimerVal, 0);
    if(lRes == -1) {printf("[GTimer2] Error GTimer2_SetItimer\n"); exit(0);}
}
//===============================================
