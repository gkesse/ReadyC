//===============================================
#ifndef _GThread2_
#define _GThread2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GThread2O GThread2O;
//===============================================
typedef void* (*GTHREAD2_CALLBACK)(void *params);
//===============================================
struct _GThread2O {
	void* m_child;
    void (*Delete)();
    void (*MallocThread)(char* threadName);
    void (*Create)(char* threadName, GTHREAD2_CALLBACK callback, void* params);
    void (*Join)(char* threadName);
    void (*Exit)(char* threadName);
    void (*FreeThread)(char* threadName);
};
//===============================================
GThread2O* GThread2_New();
void GThread2_Delete(GThread2O* obj);
GThread2O* GThread2();
//===============================================
#endif
//===============================================
