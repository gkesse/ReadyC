//===============================================
#ifndef _GThread2_
#define _GThread2_
//===============================================
#include "GInclude.h"
//===============================================
#if defined(_GUSE_THREAD_ON_)
//===============================================
typedef struct _GThread2O GThread2O;
//===============================================
struct _GThread2O {
	void* m_child;
    void (*Delete)();
    void (*Create)(char* threadId, void* onFunc, void* params);
    void (*Join)(char* threadId, int delay);
    void (*Close)(char* threadId);
};
//===============================================
GThread2O* GThread2_New();
void GThread2_Delete(GThread2O* obj);
GThread2O* GThread2();
//===============================================
#endif
//===============================================
#endif
//===============================================
