//===============================================
#ifndef _GAlarm2Unix_
#define _GAlarm2Unix_
//===============================================
#include "GAlarm2.h"
//===============================================
typedef struct _GAlarm2UnixO GAlarm2UnixO;
typedef struct _GMapO_GAlarm2Unix_GCHAR_PTR_GVOID_PTR GMapO_GAlarm2Unix_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GAlarm2UnixO {
    GAlarm2O* m_parent;
    //===============================================
    GMapO_GAlarm2Unix_GCHAR_PTR_GVOID_PTR* m_timerMap ;
    GMapO_GAlarm2Unix_GCHAR_PTR_GVOID_PTR* m_timerIdMap ;
    GMapO_GAlarm2Unix_GCHAR_PTR_GVOID_PTR* m_callbackMap ;
};
//===============================================
GAlarm2O* GAlarm2Unix_New();
void GAlarm2Unix_Delete();
GAlarm2O* GAlarm2Unix();
//===============================================
#endif
//===============================================
