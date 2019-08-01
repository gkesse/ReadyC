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
typedef struct _GMapO_GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR GMapO_GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR;
//===============================================
typedef void (*GTIMER2_SIGNAL_HANDLER)(int params);
//===============================================
struct _GTimer2O {
    void (*Delete)();
    void (*MallocTimer)(char* timerName);
    void (*MallocSignal)(char* signalName);
    void (*MallocItimer)(char* itimerName);
    void (*Timer)(char* timerName, char* signalName, int clockId);
    void (*SetTime)(char* timerName, char* itimerName);
    void (*Signal)(char* signalName, int notify, int signo, GTIMER2_SIGNAL_HANDLER callback);
    void (*Itimer)(char* itimerName, long timeT, long freq);
    void (*FreeTimer)(char* timerName);
    void (*FreeSignal)(char* signalName);
    void (*FreeItimer)(char* itimerName);
#if defined(__unix)
    GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* m_timerMap;
    GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* m_signalMap;
    GMapO(GTimer2_GCHAR_PTR_GITIMERSPEEC_PTR)* m_itimerMap;
#endif
};
//===============================================
GTimer2O* GTimer2_New();
void GTimer2_Delete();
GTimer2O* GTimer2();
//===============================================
#endif
//===============================================
