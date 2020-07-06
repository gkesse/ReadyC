//===============================================
#ifndef _GTimer2_
#define _GTimer2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GTimer2O GTimer2O;
typedef struct _GMapO_GTimer2_GCHAR_PTR_GVOID_PTR GMapO_GTimer2_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GTimer2O {
	void (*Delete)();
	void (*Timer)(char* timerName, char* sigEventName, int clockId);
	void (*SetTime)(char* timerName, char* itimerName);
	void (*Signal)(char* sigEventName, int notify, int signo, void* onFunc);
	void (*Itimer)(char* itimerName, long sec, long nsec);
	void (*InitItimerVal)(char* itimerValName, long sec, long usec);
	void (*SetItimer)(char* itimerValName, int timerId);
    //===============================================
    GMapO_GTimer2_GCHAR_PTR_GVOID_PTR* m_timerMap;
    GMapO_GTimer2_GCHAR_PTR_GVOID_PTR* m_sigEventMap;
    GMapO_GTimer2_GCHAR_PTR_GVOID_PTR* m_itimerSpecMap;
    GMapO_GTimer2_GCHAR_PTR_GVOID_PTR* m_itimerValMap;
};
//===============================================
GTimer2O* GTimer2_New();
void GTimer2_Delete();
GTimer2O* GTimer2();
//===============================================
#endif
//===============================================
