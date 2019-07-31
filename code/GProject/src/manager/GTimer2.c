//===============================================
#include "GTimer2.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR; 
typedef timer_t* GTIMERT_PTR;
typedef struct sigevent* GSIGEVENT_PTR;
typedef struct itimerspec* GITIMERSPEEC_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GTIMERT_PTR, GTimer2_GCHAR_PTR_GTIMERT_PTR)
GDEFINE_MAP(GCHAR_PTR, GTIMERT_PTR, GTimer2_GCHAR_PTR_GTIMERT_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSIGEVENT_PTR, GTimer2_GCHAR_PTR_GSIGEVENT_PTR)
GDEFINE_MAP(GCHAR_PTR, GSIGEVENT_PTR, GTimer2_GCHAR_PTR_GSIGEVENT_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GITIMERSPEEC_PTR, GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR)
GDEFINE_MAP(GCHAR_PTR, GITIMERSPEEC_PTR, GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR)
#endif
//===============================================
static GTimer2O* m_GTimer2O = 0;
//===============================================
static void GTimer2_MallocTimer(char* timerName);
static void GTimer2_MallocSignalEvent(char* signalEventName);
static void GTimer2_MallocItimer(char* itimerName);
static void GTimer2_Timer(char* timerName, char* signalEventName, int clockId);
static void GTimer2_SetTime(char* timerName, char* itimerName);
static void GTimer2_SignalEvent(char* signalEventName, int notify, int signo);
static void GTimer2_Itimer(char* itimerName, long timeT, long freq);
static void GTimer2_FreeTimer(char* timerName);
static void GTimer2_FreeSignalEvent(char* signalEventName);
static void GTimer2_FreeItimer(char* itimerName);
//===============================================
#if defined(__unix)
static int GTimer2_MapEqual(char* key1, char* key2); 
#endif
//===============================================
GTimer2O* GTimer2_New() {
    GTimer2O* lObj = (GTimer2O*)malloc(sizeof(GTimer2O));
    
#if defined(__unix)
	lObj->m_timerMap = GMap_New_GTimer2_GCHAR_PTR_GTIMERT_PTR();
	lObj->m_signalEventMap = GMap_New_GTimer2_GCHAR_PTR_GSIGEVENT_PTR();
	lObj->m_itimerMap = GMap_New_GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR();
#endif
    
    lObj->Delete = GTimer2_Delete;
    lObj->MallocTimer = GTimer2_MallocTimer;
    lObj->MallocSignalEvent = GTimer2_MallocSignalEvent;
    lObj->MallocItimer = GTimer2_MallocItimer;
    lObj->Timer = GTimer2_Timer;
    lObj->SetTime = GTimer2_SetTime;
    lObj->SignalEvent = GTimer2_SignalEvent;
    lObj->Itimer = GTimer2_Itimer;
    lObj->FreeTimer = GTimer2_FreeTimer;
    lObj->FreeSignalEvent = GTimer2_FreeSignalEvent;
    lObj->FreeItimer = GTimer2_FreeItimer;
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
static void GTimer2_MallocSignalEvent(char* signalEventName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalEventMap = m_GTimer2O->m_signalEventMap;
	struct sigevent* lSignalEvent = (struct sigevent*)malloc(sizeof(struct sigevent));
	if(lSignalEvent == 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_MallocSignalEvent\n");  exit(0);}
	lSignalEventMap->SetData(lSignalEventMap, signalEventName, lSignalEvent, GTimer2_MapEqual);
#endif
}
//===============================================
static void GTimer2_MallocItimer(char* itimerName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR)* lItimerMap = m_GTimer2O->m_itimerMap;
	struct itimerspec* lItimer = (struct itimerspec*)malloc(sizeof(struct itimerspec));
	if(lItimer == 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_MallocItimer\n");  exit(0);}
	lItimerMap->SetData(lItimerMap, itimerName, lItimer, GTimer2_MapEqual);
#endif
}
//===============================================
static void GTimer2_Timer(char* timerName, char* signalName, int clockId) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalMap = m_GTimer2O->m_signalMap;
	timer_t* lTimer = lTimerMap->GetData(lTimerMap, timerName, GTimer2_MapEqual);
	struct sigevent* lSignal = lSignalMap->GetData(lSignalMap, signalName, GTimer2_MapEqual);
	int lRes = timer_create(clockId, lSignal, lTimer);
    if(lRes != 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_Timer\n"); exit(0);}
#endif
}
//===============================================
static void GTimer2_SetTime(char* timerName, char* itimerName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* lTimerMap = m_GTimer2O->m_timerMap;
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR)* lItimerMap = m_GTimer2O->m_itimerMap;
	timer_t* lTimer = lTimerMap->GetData(lTimerMap, timerName, GTimer2_MapEqual);
	struct itimerspec* lItimer = lItimerMap->GetData(lItimerMap, itimerName, GTimer2_MapEqual);
	int lRes = timer_settime(*lTimer, 0, lItimer, 0);
    if(lRes != 0) {GConsole()->Print("[ GTimer2 ] Error GTimer2_SetTime\n"); exit(0);}
#endif
}
//===============================================
static void GTimer2_Signal(char* signalName, int notify, int signo) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalMap = m_GTimer2O->m_signalMap;
	struct sigevent* lSignal = lSignalMap->GetData(lSignalMap, signalName, GTimer2_MapEqual);
	lSignal->sigev_notify = notify;
	lSignal->sigev_signo  = signo;
#endif
}
//===============================================
static void GTimer2_Itimer(char* itimerName, long timeT, long freq) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR)* lItimerMap = m_GTimer2O->m_itimerMap;
	struct itimerspec* lItimer = lItimerMap->GetData(lItimerMap, itimerName, GTimer2_MapEqual);
	lItimer->it_value.tv_sec = timeT;
	lItimer->it_value.tv_nsec = 1000000000/freq;
	lItimer->it_interval.tv_sec = timeT;
	lItimer->it_interval.tv_nsec = 1000000000/freq;
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
	GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* lSignalMap = m_GTimer2O->m_signalMap;
	struct sigevent* lSignal = lSignalMap->GetData(lSignalMap, signalName, GTimer2_MapEqual);
    free(lSignal);
#endif
}
//===================================== ==========
static void GTimer2_FreeItimer(char* itimerName) {
#if defined(__unix)
	GMapO(GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR)* lItimerMap = m_GTimer2O->m_itimerMap;
	struct itimerspec* lItimer = lItimerMap->GetData(lItimerMap, itimerName, GTimer2_MapEqual);
    free(lItimer);
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
