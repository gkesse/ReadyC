//===============================================
#ifndef _GSignal_
#define _GSignal_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSignalO GSignalO;
typedef struct _GMapO_GSignal_GCHAR_PTR_GSIGACTION_PTR GMapO_GSignal_GCHAR_PTR_GSIGACTION_PTR;
typedef void (*GSIGNAL_CALLBACK)(int signo);
//===============================================
struct _GSignalO {
    void (*Delete)();
    void (*MallocSigAction)(char* sigActionName);
    void (*InitSigAction)(char* sigActionName, GSIGNAL_CALLBACK callback, int flags);
    void (*SetSigAction)(char* sigActionName, int signalId);
#if defined(__unix)
	GMapO(GSignal_GCHAR_PTR_GSIGACTION_PTR)* m_sigActionMap;
#endif
};
//===============================================
GSignalO* GSignal_New();
void GSignal_Delete();
GSignalO* GSignal();
//===============================================
#endif
//===============================================
