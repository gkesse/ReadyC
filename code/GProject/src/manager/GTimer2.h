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
typedef void (*GTIMER2_SIGNAL_HANDLER)(int);
//===============================================
struct _GTimer2O {
    void (*Delete)();
    void (*MallocTimer)(char* timerName);
    void (*MallocSignal)(char* signalName);
    void (*Timer)(char* timerName, char* signalName, int clockId);
    void (*Signal)(char* signalName, int notify, int signo);
    void (*FreeTimer)(char* timerName);
    void (*FreeSignal)(char* signalName);
#if defined(__unix)
    GMapO(GTimer2_GCHAR_PTR_GTIMERT_PTR)* m_timerMap;
    GMapO(GTimer2_GCHAR_PTR_GSIGEVENT_PTR)* m_signalMap;
#endif
};
//===============================================
GTimer2O* GTimer2_New();
void GTimer2_Delete();
GTimer2O* GTimer2();
//===============================================
#endif
//===============================================
