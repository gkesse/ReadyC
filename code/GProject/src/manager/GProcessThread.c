//===============================================
#include "GProcessThread.h"
#include "GConsole.h"
#include "GThread2.h"
#include "GSleep.h"
//===============================================
static GProcessO* m_GProcessThreadO = 0;
//===============================================
static void GProcessThread_Run(int argc, char** argv);
//===============================================
static GTHREAD2_RET GProcessThread_ThreadA(void* params);
static GTHREAD2_RET GProcessThread_ThreadB(void* params);
//===============================================
GProcessO* GProcessThread_New() {
	GProcessO* lParent = GProcess_New();
	GProcessThreadO* lChild = (GProcessThreadO*)malloc(sizeof(GProcessThreadO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessThread_Delete;
	lParent->Run = GProcessThread_Run;
	return lParent;
}
//===============================================
void GProcessThread_Delete() {
	GProcess_Delete(m_GProcessThreadO);
	m_GProcessThreadO = 0;
}
//===============================================
GProcessO* GProcessThread() {
	if(m_GProcessThreadO == 0) {
		m_GProcessThreadO = GProcessThread_New();
	}
	return m_GProcessThreadO;
}
//===============================================
static void GProcessThread_Run(int argc, char** argv) {
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis un thread\n");
    GConsole()->Print("=================================================\n");
	GThread2()->MallocThread("THREAD_A");
	GThread2()->MallocThread("THREAD_B");

	GThread2()->Create("THREAD_A", GProcessThread_ThreadA, 0);
	GThread2()->Create("THREAD_B", GProcessThread_ThreadB, 0);

	GThread2()->Join("THREAD_A");
	GThread2()->Join("THREAD_B");

	GThread2()->FreeThread("THREAD_A");
	GThread2()->FreeThread("THREAD_B");
    GConsole()->Print("=================================================\n");
}
//===============================================
static GTHREAD2_RET GProcessThread_ThreadA(void* params) {
    while(1) {
        GConsole()->Print("Je suis le thread Thread_A\n");
        GSleep()->Sleep(3);
    }
	return 0;
}
//===============================================
static GTHREAD2_RET GProcessThread_ThreadB(void* params) {
    while(1) {
        GConsole()->Print("Je suis le thread Thread_B\n");
        GSleep()->Sleep(3);
    }
	return 0;
}
//===============================================
