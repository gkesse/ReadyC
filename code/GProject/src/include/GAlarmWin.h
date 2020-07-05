//===============================================
#ifndef _GAlarmWin_
#define _GAlarmWin_
//===============================================
#include "GAlarm.h"
//===============================================
typedef struct _GAlarmWinO GAlarmWinO;
typedef struct _GMapO_GAlarmWin_GCHAR_PTR_GVOID_PTR GMapO_GAlarmWin_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GAlarmWinO {
    GAlarmO* m_parent;
    //===============================================
    GMapO_GAlarmWin_GCHAR_PTR_GVOID_PTR* m_timerMap ;
    GMapO_GAlarmWin_GCHAR_PTR_GVOID_PTR* m_timerIdMap ;
    GMapO_GAlarmWin_GCHAR_PTR_GVOID_PTR* m_callbackMap ;
};
//===============================================
GAlarmO* GAlarmWin_New();
void GAlarmWin_Delete();
GAlarmO* GAlarmWin();
//===============================================
#endif
//===============================================
