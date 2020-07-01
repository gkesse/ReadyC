//===============================================
#ifndef _GAlarm2Win_
#define _GAlarm2Win_
//===============================================
#include "GAlarm2.h"
//===============================================
typedef struct _GAlarm2WinO GAlarm2WinO;
typedef struct _GMapO_GAlarm2Win_GCHAR_PTR_GVOID_PTR GMapO_GAlarm2Win_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GAlarm2WinO {
    GAlarm2O* m_parent;
    //===============================================
    GMapO_GAlarm2Win_GCHAR_PTR_GVOID_PTR* m_timerMap ;
    GMapO_GAlarm2Win_GCHAR_PTR_GVOID_PTR* m_timerIdMap ;
    GMapO_GAlarm2Win_GCHAR_PTR_GVOID_PTR* m_callbackMap ;
};
//===============================================
GAlarm2O* GAlarm2Win_New();
void GAlarm2Win_Delete();
GAlarm2O* GAlarm2Win();
//===============================================
#endif
//===============================================
