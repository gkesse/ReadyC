//===============================================
#ifndef _GAlarmUnix_
#define _GAlarmUnix_
//===============================================
#include "GAlarm.h"
//===============================================
typedef struct _GAlarmUnixO GAlarmUnixO;
typedef struct _GMapO_GAlarmUnix_GCHAR_PTR_GVOID_PTR GMapO_GAlarmUnix_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GAlarmUnixO {
    GAlarmO* m_parent;
    //===============================================
    GMapO_GAlarmUnix_GCHAR_PTR_GVOID_PTR* m_timerMap ;
    GMapO_GAlarmUnix_GCHAR_PTR_GVOID_PTR* m_timerIdMap ;
    GMapO_GAlarmUnix_GCHAR_PTR_GVOID_PTR* m_callbackMap ;
};
//===============================================
GAlarmO* GAlarmUnix_New();
void GAlarmUnix_Delete();
GAlarmO* GAlarmUnix();
//===============================================
#endif
//===============================================
