//===============================================
#include "GProcessThread.h"
#include "GConsole.h"
#include "GThread2.h"
//===============================================
static GProcessO* m_GProcessThreadO = 0;
//===============================================
static void GProcessThread_Run(int argc, char** argv);
static void* GProcessThread_ThreadA(void* params);
static void* GProcessThread_ThreadB(void* params);
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
	GThread2()->MallocThread("THREAD_A");
	GThread2()->MallocThread("THREAD_B");
	GConsole()->Print("PASS\n");

	GThread2()->Create("THREAD_A", GProcessThread_ThreadA, "LED_A");
	GThread2()->Create("THREAD_B", GProcessThread_ThreadB, "LED_B");

	GThread2()->Join("THREAD_A");
	GThread2()->Join("THREAD_B");

	GThread2()->FreeThread("THREAD_A");
	GThread2()->FreeThread("THREAD_B");
}
//===============================================
static void* GProcessThread_ThreadA(void* params) {
	char* lParams = (char*)params;
	for(int i = 0; i < 20; i++) {
		GConsole()->Print("ThreadA : GConsole Thread-Safe ??? : %s\n", lParams);
		sleep(5);
	}
	return 0;
}
//===============================================
static void* GProcessThread_ThreadB(void* params) {
	char* lParams = (char*)params;
	for(int i = 0; i < 20; i++) {
		GConsole()->Print("ThreadB : GConsole Thread-Safe ??? : %s\n", lParams);
		sleep(5);
	}
	return 0;
}
//===============================================
