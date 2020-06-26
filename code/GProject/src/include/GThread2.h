//===============================================
#ifndef _GThread2_
#define _GThread2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GThread2O GThread2O;
//===============================================
#if defined(__unix)
#define GTHREAD2_RET void*
#elif defined(__WIN32)
#define GTHREAD2_RET unsigned __stdcall
#endif
//===============================================
typedef GTHREAD2_RET (*GTHREAD2_CREATE_CALLBACK)(void *params);
typedef GTHREAD2_CREATE_CALLBACK GTHREAD2_BEGIN_CALLBACK;
//===============================================
typedef enum _GTHREAD2_INITIALIZER {
	GTHREAD2_INIT_INFINITE
} GTHREAD2_INITIALIZER;
//===============================================
struct _GThread2O {
	void* m_child;
    void (*Delete)();
    // UNIX
    void (*MallocThread)(char* threadName);
    void (*Create)(char* threadName, GTHREAD2_CREATE_CALLBACK callback, void* params);
    void (*Join)(char* threadName);
    void (*Exit)(char* threadName);
    void (*FreeThread)(char* threadName);
    // WINDOWS
    void (*BeginThread)(char* threadName, GTHREAD2_BEGIN_CALLBACK callback, void* params);
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
