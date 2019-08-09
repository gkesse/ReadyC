//===============================================
#include "GTimer2.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR; 
typedef timer_t* GTIMERT_PTR;
typedef struct sigevent* GSIGEVENT_PTR;
typedef struct itimerspec* GITIMERSPEC_PTR;
typedef struct itimerval* GITIMERVAL_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GTIMERT_PTR, GTimer2_GCHAR_PTR_GTIMERT_PTR)
GDEFINE_MAP(GCHAR_PTR, GTIMERT_PTR, GTimer2_GCHAR_PTR_GTIMERT_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSIGEVENT_PTR, GTimer2_GCHAR_PTR_GSIGEVENT_PTR)
GDEFINE_MAP(GCHAR_PTR, GSIGEVENT_PTR, GTimer2_GCHAR_PTR_GSIGEVENT_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GITIMERSPEC_PTR, GTimer2_GCHAR_PTR_GITIMERSPEC_PTR)
GDEFINE_MAP(GCHAR_PTR, GITIMERSPEC_PTR, GTimer2_GCHAR_PTR_GITIMERSPEC_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GITIMERVAL_PTR, GTimer2_GCHAR_PTR_GITIMERVAL_PTR)
GDEFINE_MAP(GCHAR_PTR, GITIMERVAL_PTR, GTimer2_GCHAR_PTR_GITIMERVAL_PTR)
#endif
//===============================================
static GTimer2O* m_GTimer2O = 0;
//===============================================
static void GTimer2_MallocTimer(char* timerName);
static void GTimer2_MallocSigEvent(char* signalName);
static void GTimer2_MallocItimerSpec(char* itimerSpecName);
static void GTimer2_MallocItimerVal(char* itimerValName);
static void GTimer2_Timer(char* timerName, char* signalName, int clockId);
static void GTimer2_SetTime(char* timerName, char* itimerSpecName);
static void GTimer2_Signal(char* signalName, int notify, int signo, GTIMER2_SIGNAL_HANDLER callback);
static void GTimer2_Itimer(char* itimerSpecName, long sec, long nsec);
static void GTimer2_InitItimerVal(char* itimerValName, long sec, long usec);
static void GTimer2_SetItimer(char* itimerValName, int timerId);
static void GTimer2_FreeTimer(char* timerName);
static void GTimer2_FreeSignal(char* signalName);
static void GTimer2_FreeItimer(char* itimerSpecName);
static void GTimer2_FreeItimerVal(char* itimerValName);
//===============================================
#if defined(__unix)
static int GTimer2_MapEqual(char* key1, char* key2); 
#endif
//===============================================
GTimer2O* GTimer2_New() {
    GTimer2O* lObj = (GTimer2O*)malloc(sizeof(GTimer2O));
    
#if defined(__unix)
	lObj->m_timerMap = GMap_New_GTimer2_GCHAR_PTR_GTIMERT_PTR();
	lObj->m_sigEventMap = GMap_New_GTimer2_GCHAR_PTR_GSIGEVENT_PTR();
	lObj->m_itimerSpecMap = GMap_New_GTimer2_GCHAR_PTR_GITIMERSPEC_PTR();
	lObj->m_itimerValMap = GMap_New_GTimer2_GCHAR_PTR_GITIMERVAL_PTR();
#endif
    
    lObj->Delete = GTimer2_Delete;
    lObj->MallocTimer = GTimer2_MallocTimer;
    lObj->MallocSigEvent = GTimer2_MallocSigEvent;
    lObj->MallocItimer = GTimer2_MallocItimer;
    lObj->MallocItimerVal = GTimer2_MallocItimerVal;
    lObj->Timer = GTimer2_Timer;
    lObj->SetTime = GTimer2_SetTime;
    lObj->Signal = GTimer2_Signal;
    lObj->Itimer = GTimer2_Itimer;
    lObj->Itimer = GTimer2_Itimer;
    lObj->InitItimerVal = GTimer2_InitItimerVal;
    lObj->SetItimer = GTimer2_SetItimer;
    lObj->FreeTimer = GTimer2_FreeTimer;
    lObj->FreeSignal = GTimer2_FreeSignal;
    lObj->FreeItimer = GTimer2_FreeItimer;
    lObj->FreeItimerVal = GTimer2_FreeItimerVal;
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
static void GTimer2_MallocTimer(char* timerName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
	timer_t* lTimer = (timer_t*)malloc(sizeof(timer_t));
	if(lTimer == 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_MallocThread\n");  exit(0);}
	lTimerMap->SetData(lTimerMap, timerName, lTimer, GTimer2_MapEqual);
#endif
}
//===============================================
static void GTimer2_MallocSigEvent(char* signalName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalMap = m_GTimer2O->m_sigEventMap;
	struct sigevent* lSignal = (struct sigevent*)malloc(sizeof(struct sigevent));
	if(lSignal == 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_MallocSigEvent\n");  exit(0);}
	lSignalMap->SetData(lSignalMap, signalName, lSignal, GTimer2_MapEqual);
#endif
}
//===============================================
static void GTimer2_MallocItimerSpec(char* itimerSpecName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEC_PTR)* lItimerSpecMap = m_GTimer2O->m_itimerSpecMap;
	struct itimerspec* lItimerSpec = (struct itimerspec*)malloc(sizeof(struct itimerspec));
	if(lItimerSpec == 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_MallocItimerSpec\n");  exit(0);}
	lItimerSpecMap->SetData(lItimerSpecMap, itimerSpecName, lItimerSpec, GTimer2_MapEqual);
#endif
}
//===============================================
static void GTimer2_MallocItimerVal(char* itimerValName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERVAL_PTR)* lItimerValMap = m_GTimer2O->m_itimerValMap;
	struct itimerval* lItimerVal = (struct itimerval*)malloc(sizeof(struct itimerval));
	if(lItimerVal == 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_MallocItimerVal\n");  exit(0);}
	lItimerValMap->SetData(lItimerValMap, itimerValName, lItimerVal, GTimer2_MapEqual);
#endif
}
//===============================================
static void GTimer2_Timer(char* timerName, char* signalName, int clockId) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalMap = m_GTimer2O->m_sigEventMap;
	timer_t* lTimer = lTimerMap->GetData(lTimerMap, timerName, GTimer2_MapEqual);
	struct sigevent* lSignal = lSignalMap->GetData(lSignalMap, signalName, GTimer2_MapEqual);
	int lRes = timer_create(clockId, lSignal, lTimer);
    if(lRes != 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_Timer\n"); exit(0);}
#endif
}
//===============================================
static void GTimer2_SetTime(char* timerName, char* itimerSpecName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEC_PTR)* lItimerSpecMap = m_GTimer2O->m_itimerSpecMap;
	timer_t* lTimer = lTimerMap->GetData(lTimerMap, timerName, GTimer2_MapEqual);
	struct itimerspec* lItimerSpec = lItimerSpecMap->GetData(lItimerSpecMap, itimerSpecName, GTimer2_MapEqual);
	int lRes = timer_settime(*lTimer, 0, lItimerSpec, 0);
    if(lRes != 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_SetTime\n"); exit(0);}
#endif
}
//===============================================
static void GTimer2_Signal(char* signalName, int notify, int signo, GTIMER2_SIGNAL_HANDLER callback) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalMap = m_GTimer2O->m_sigEventMap;
	struct sigevent* lSignal = lSignalMap->GetData(lSignalMap, signalName, GTimer2_MapEqual);
	lSignal->sigev_notify = notify;
	lSignal->sigev_signo  = signo;
	signal(signo, callback);
#endif
}
//===============================================
static void GTimer2_Itimer(char* itimerSpecName, long sec, long nsec) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEC_PTR)* lItimerSpecMap = m_GTimer2O->m_itimerSpecMap;
	struct itimerspec* lItimerSpec = lItimerSpecMap->GetData(lItimerSpecMap, itimerSpecName, GTimer2_MapEqual);
	lItimerSpec->it_value.tv_sec = sec;
	lItimerSpec->it_value.tv_nsec = nsec;
	lItimerSpec->it_interval.tv_sec = sec;
	lItimerSpec->it_interval.tv_nsec = nsec;
#endif
}
//===============================================
static void GTimer2_InitItimerVal(char* itimerValName, long sec, long usec) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERVAL_PTR)* lItimerValMap = m_GTimer2O->m_itimerValMap;
	struct itimerval* lItimerVal = lItimerValMap->GetData(lItimerValMap, itimerValName, GTimer2_MapEqual);
	lItimerVal->it_value.tv_sec = sec;
	lItimerVal->it_value.tv_usec = usec;
	lItimerVal->it_interval.tv_sec = sec;
	lItimerVal->it_interval.tv_usec = usec;
#endif
}
//===============================================
static void GTimer2_SetItimer(char* itimerValName, int timerId) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERVAL_PTR)* lItimerValMap = m_GTimer2O->m_itimerValMap;
	struct itimerval* lItimerVal = lItimerValMap->GetData(lItimerValMap, itimerValName, GTimer2_MapEqual);
    int lRes = setitimer(timerId, lItimerVal, 0);
    if(lRes == -1) {GConsole()->Print("[ GTimer2 ] Error GTimer2_SetItimer\n"); exit(0);}
#endif
}
//===============================================
static void GTimer2_FreeTimer(char* timerName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
	timer_t* lTimer = lTimerMap->GetData(lTimerMap, timerName, GTimer2_MapEqual);
    free(lTimer);
#endif
}
//===============================================
static void GTimer2_FreeSignal(char* signalName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalMap = m_GTimer2O->m_sigEventMap;
	struct sigevent* lSignal = lSignalMap->GetData(lSignalMap, signalName, GTimer2_MapEqual);
    free(lSignal);
#endif
}
//===================================== ==========
static void GTimer2_FreeItimer(char* itimerSpecName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEC_PTR)* lItimerSpecMap = m_GTimer2O->m_itimerSpecMap;
	struct itimerspec* lItimerSpec = lItimerSpecMap->GetData(lItimerSpecMap, itimerSpecName, GTimer2_MapEqual);
    free(lItimerSpec);
#endif
}
//===================================== ==========
static void GTimer2_FreeItimerVal(char* itimerValName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERVAL_PTR)* lItimerValMap = m_GTimer2O->m_itimerValMap;
	struct itimerval* lItimerVal = lItimerValMap->GetData(lItimerValMap, itimerValName, GTimer2_MapEqual);
    free(lItimerVal);
#endif
}
//===============================================
#if defined(__unix)
static int GTimer2_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
#endif
//===============================================
