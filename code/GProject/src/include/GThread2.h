//===============================================
#ifndef _GThread2_
#define _GThread2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GThread2O GThread2O;
//===============================================
struct _GThread2O {
	void* m_child;
    void (*Delete)();
    void (*Create)(char* threadName, void onFunc, void* params);
    void (*Join)(char* threadName);
    void (*Exit)(char* threadName);
    void (*FreeThread)(char* threadName);
    void (*BeginThread)(char* threadName, void* callback, void* params);
    void (*WaitForSingleObject)(char* threadName, int delay);
    void (*CloseHandle)(char* threadName);
};
//===============================================
GThread2O* GThread2_New();
void GThread2_Delete(GThread2O* obj);
GThread2O* GThread2();
//===============================================
#endif
//===============================================
