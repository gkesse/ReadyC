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
typedef enum _GSIGNAL_INITIALIZER {
	GSIGNAL_SIGALRM,
	GSIGNAL_SIGINT,
	GSIGNAL_ITIMER_REAL
} GSIGNAL_INITIALIZER;
//===============================================
struct _GSignalO {
    void (*Delete)();
    void (*MallocSigAction)(char* sigActionName);
    void (*MallocSigJmpBuf)(char* sigJmpBufName);
    void (*InitSigAction)(char* sigActionName, GSIGNAL_CALLBACK callback, int flags);
    void (*SigFillSet)(char* sigActionName);
    void (*SigDelSet)(char* sigActionName, int signalId);
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
#if defined(__unix)
#define GSIGNAL_INITIALIZER_SET(GENUM) \
		switch(GENUM) { \
		case GSIGNAL_SIGALRM: SIGALRM; break; \
		case GSIGNAL_SIGINT: SIGINT; break; \
		case GSIGNAL_SIGALRM: SIGALRM; break; \
		default: break; \
		}
#endif
//===============================================
#endif
//===============================================
