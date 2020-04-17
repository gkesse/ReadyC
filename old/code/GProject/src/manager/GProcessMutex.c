//===============================================
#include "GProcessMutex.h"
#include "GMutex2.h"
#include "GThread2.h"
#include "GSleep.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessMutexO = 0;
//===============================================
static void GProcessMutex_Run(int argc, char** argv);
//===============================================
static GTHREAD2_RET GProcessMutex_Callback(void* params);
//===============================================
GProcessO* GProcessMutex_New() {
    GProcessO* lParent = GProcess_New();
    GProcessMutexO* lChild = (GProcessMutexO*)malloc(sizeof(GProcessMutexO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessMutex_Delete;
    lParent->Run = GProcessMutex_Run;
    return lParent;
}
//===============================================
void GProcessMutex_Delete() {
	GProcess_Delete(m_GProcessMutexO);
    m_GProcessMutexO = 0;
}
//===============================================
GProcessO* GProcessMutex() {
    if(m_GProcessMutexO == 0) {
        m_GProcessMutexO = GProcessMutex_New();
    }
    return m_GProcessMutexO;
}
//===============================================
static void GProcessMutex_Run(int argc, char** argv) {
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis un mutex\n");
    GConsole()->Print("=================================================\n");
    GMutex2()->MallocThreadMutex("MUTEX"); 
    GThread2()->MallocThread("THREAD_A");
	GThread2()->MallocThread("THREAD_B");

    GMutex2()->InitThreadMutex("MUTEX", GMUTEX2_INIT_PTHREAD_MUTEX_INITIALIZER);
	GThread2()->Create("THREAD_A", GProcessMutex_Callback, "THREAD_A");
	GThread2()->Create("THREAD_B", GProcessMutex_Callback, "THREAD_B");
	GThread2()->Join("THREAD_A");
	GThread2()->Join("THREAD_B");

	GThread2()->FreeThread("THREAD_A");
	GThread2()->FreeThread("THREAD_B");
    GMutex2()->FreeThreadMutex("MUTEX");
    GConsole()->Print("=================================================\n");
}
//===============================================
static GTHREAD2_RET GProcessMutex_Callback(void* params) {
    char* lThread = (char*)params;
    while(1) {
        GSleep()->Sleep(1);
        GMutex2()->MutexLock("MUTEX");
        GConsole()->Print("Je suis le thread : %s\n", lThread);
        GSleep()->Sleep(1);
        GMutex2()->MutexUnlock("MUTEX");
    }
	return 0;
}
//===============================================
