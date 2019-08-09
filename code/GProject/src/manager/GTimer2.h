//===============================================
#ifndef _GTimer2_
#define _GTimer2_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GTimer2O GTimer2O;
typedef struct _GMapO_GTimer2_GCHAR_PTR_GTIMERT_PTR GMapO_GTimer2_GCHAR_PTR_GTIMERT_PTR;
typedef struct _GMapO_GTimer2_GCHAR_PTR_GSIGEVENT_PTR GMapO_GTimer2_GCHAR_PTR_GSIGEVENT_PTR;
typedef struct _GMapO_GTimer2_GCHAR_PTR_GITIMERSPEC_PTR GMapO_GTimer2_GCHAR_PTR_GITIMERSPEC_PTR;
typedef struct _GMapO_GTimer2_GCHAR_PTR_GITIMERVAL_PTR GMapO_GTimer2_GCHAR_PTR_GITIMERVAL_PTR;
//===============================================
typedef void (*GTIMER2_SIGNAL_HANDLER)(int params);
//===============================================
struct _GTimer2O {
    void (*Delete)();
    void (*MallocTimer)(char* timerName);
    void (*MallocSigEvent)(char* sigEventName);
    void (*MallocItimerSpec)(char* itimerSpecName);
    void (*MallocItimerVal)(char* itimerValName);
    void (*Timer)(char* timerName, char* sigEventName, int clockId);
    void (*SetTime)(char* timerName, char* itimerName);
    void (*Signal)(char* sigEventName, int notify, int signo, GTIMER2_SIGNAL_HANDLER callback);
    void (*Itimer)(char* itimerName, long sec, long nsec);
    void (*InitItimerVal)(char* itimerValName, long sec, long usec);
    void (*SetItimer)(char* itimerValName, int timerId);
    void (*FreeTimer)(char* timerName);
    void (*FreeSigEvent)(char* sigEventName);
    void (*FreeItimerSpec)(char* itimerSpecName);
    void (*FreeItimerVal)(char* itimerValName);
#if defined(__unix)
    GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* m_timerMap;
    GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* m_sigEventMap;
    GMapO(GTimer2_GCHAR_PTR_GITIMERSPEC_PTR)* m_itimerSpecMap;
    GMapO(GTimer2_GCHAR_PTR_GITIMERVAL_PTR)* m_itimerValMap;
#endif
};
//===============================================
GTimer2O* GTimer2_New();
void GTimer2_Delete();
GTimer2O* GTimer2();
//===============================================
#endif
//===============================================
