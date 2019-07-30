//===============================================
#ifndef _GThread2_
#define _GThread2_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GThread2O GThread2O;
typedef struct _GMapO_GThread2_GCHAR_PTR_GPTHREADT_PTR GMapO_GThread2_GCHAR_PTR_GPTHREADT_PTR;
typedef void* (*GTHREAD2_CALLBACK)(void *params);
//===============================================
struct _GThread2O {
    void (*Delete)();
    void (*MallocThread)(char* threadName);
    void (*Create)(char* threadName, GTHREAD2_CALLBACK callback, void* params);
    void (*Join)(char* threadName);
    void (*Exit)(char* threadName);
    void (*FreeThread)(char* threadName);
#if defined(__unix)
	GMapO(GThread2_GCHAR_PTR_GPTHREADT_PTR)* m_threadMap;
#endif
};
//===============================================
GThread2O* GThread2_New();
void GThread2_Delete();
GThread2O* GThread2();
//===============================================
#endif
//===============================================
