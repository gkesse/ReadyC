//===============================================
#include "GProcessTimerInterval.h"
#include "GSignal.h"
#include "GMainLoop2.h"
#include "GTimer2.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessTimerIntervalO = 0;
//===============================================
static void GProcessTimerInterval_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessTimerInterval_New() {
	GProcessO* lParent = GProcess_New();
	GProcessTimerIntervalO* lChild = (GProcessTimerIntervalO*)malloc(sizeof(GProcessTimerIntervalO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessTimerInterval_Delete;
	lParent->Run = GProcessTimerInterval_Run;
	return lParent;
}
//===============================================
void GProcessTimerInterval_Delete() {
	GProcess_Delete(m_GProcessTimerIntervalO);
	m_GProcessTimerIntervalO = 0;
}
//===============================================
GProcessO* GProcessTimerInterval() {
	if(m_GProcessTimerIntervalO == 0) {
		m_GProcessTimerIntervalO = GProcessTimerInterval_New();
	}
	return m_GProcessTimerIntervalO;
}
//===============================================
static void GProcessTimerInterval_Callback(int signo) {
    GConsole()->Print("Je suis la fonction de rappel...\n");
}
//===============================================
static void GProcessTimerInterval_Run(int argc, char** argv) {
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis un timer [ setitimer ]\n");
    GConsole()->Print("=================================================\n");
    GSignal()->MallocSigAction("TIMER");
    GTimer2()->MallocItimerVal("TIMER");
    
    GSignal()->InitSigAction("TIMER", GProcessTimerInterval_Callback, 0);
    GTimer2()->InitItimerVal("TIMER", 0, 200000);
    
    GSignal()->SigFillSet("TIMER");
    GSignal()->SigDelSet("TIMER", SIGALRM);
    GSignal()->SigDelSet("TIMER", SIGINT);
    GSignal()->SigAction("TIMER", SIGALRM);
    GTimer2()->SetItimer("TIMER", ITIMER_REAL);
    GMainLoop2()->Run();
    
    GSignal()->FreeSigAction("TIMER");
    GTimer2()->FreeItimerVal("TIMER");
    GConsole()->Print("=================================================\n");
}
//===============================================
