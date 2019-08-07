//===============================================
#ifndef _GSignal_
#define _GSignal_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSignalO GSignalO;
typedef struct _GMapO_GSignal_GCHAR_PTR_GSIGACTION_PTR GMapO_GSignal_GCHAR_PTR_GSIGACTION_PTR;
typedef struct _GMapO_GSignal_GCHAR_PTR_GSIGJMPBUF_PTR GMapO_GSignal_GCHAR_PTR_GSIGJMPBUF_PTR;
typedef void (*GSIGNAL_CALLBACK)(int signo);
//===============================================
struct _GSignalO {
    void (*Delete)();
    void (*MallocSigAction)(char* sigActionName);
    void (*MallocSigJmpBuf)(char* sigJmpBufName);
    void (*SigFillSet)(char* sigActionName);
    void (*InitSigAction)(char* sigActionName, GSIGNAL_CALLBACK callback, int flags);
    void (*SigLongJmp)(char* sigJmpBufName, int val);
    int (*SigSetJmp)(char* sigJmpBufName, int saveSigs);
    void (*SigAction)(char* sigActionName, int signalId);
    void (*FreeSigAction)(char* sigActionName);
    void (*FreeSigJmpBuf)(char* sigJmpBufName);
#if defined(__unix)
	GMapO(GSignal_GCHAR_PTR_GSIGACTION_PTR)* m_sigActionMap;
	GMapO(GSignal_GCHAR_PTR_GSIGJMPBUF_PTR)* m_sigJmpBufMap;
#endif
};
//===============================================
GSignalO* GSignal_New();
void GSignal_Delete();
GSignalO* GSignal();
//===============================================
#endif
//===============================================
