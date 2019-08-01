//===============================================
#include "GProcessTimer.h"
#include "GTimer2.h"
//===============================================
static GProcessO* m_GProcessTimerO = 0;
//===============================================
static void GProcessTimer_Run(int argc, char** argv);
static void GProcessTimer_TimerA(int params);
//===============================================
GProcessO* GProcessTimer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessTimerO* lChild = (GProcessTimerO*)malloc(sizeof(GProcessTimerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessTimer_Delete;
	lParent->Run = GProcessTimer_Run;
	return lParent;
}
//===============================================
void GProcessTimer_Delete() {
	GProcess_Delete(m_GProcessTimerO);
	m_GProcessTimerO = 0;
}
//===============================================
GProcessO* GProcessTimer() {
	if(m_GProcessTimerO == 0) {
		m_GProcessTimerO = GProcessTimer_New();
	}
	return m_GProcessTimerO;
}
//===============================================
static void GProcessTimer_Run(int argc, char** argv) {
	GTimer2()->MallocTimer("TIMER");
	GTimer2()->MallocSignal("TIMER");
	GTimer2()->MallocItimer("TIMER");
    
	GTimer2()->Signal("TIMER", SIGEV_SIGNAL, SIGUSR1, GProcessTimer_TimerA);
	GTimer2()->Itimer("TIMER", 0, 10);
	GTimer2()->Timer("TIMER", "TIMER", CLOCK_REALTIME);

	GTimer2()->FreeTimer("TIMER");
	GTimer2()->FreeSignal("TIMER");
	GTimer2()->FreeItimer("TIMER");
    
    while(1) {
        pause();
    }
}
//===============================================
static void GProcessTimer_TimerA(int params) {
	printf("Je suis le timer A\n");
}
//===============================================
