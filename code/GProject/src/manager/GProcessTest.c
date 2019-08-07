//===============================================
#include "GProcessTest.h"
#include "GSignal.h"
#include "GMainLoop2.h"
#include "GAlarm.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessTestO = 0;
//===============================================
static void GProcessTest_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessTest_New() {
	GProcessO* lParent = GProcess_New();
	GProcessTestO* lChild = (GProcessTestO*)malloc(sizeof(GProcessTestO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessTest_Delete;
	lParent->Run = GProcessTest_Run;
	return lParent;
}
//===============================================
void GProcessTest_Delete() {
	GProcess_Delete(m_GProcessTestO);
	m_GProcessTestO = 0;
}
//===============================================
GProcessO* GProcessTest() {
	if(m_GProcessTestO == 0) {
		m_GProcessTestO = GProcessTest_New();
	}
	return m_GProcessTestO;
}
//===============================================
static void GProcessTest_Callback(int signo) {
    GConsole()->Print("Je suis la fonction de rappel...\n");
}
//===============================================
static void GProcessTest_Run(int argc, char** argv) {
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis un timer\n");
    GConsole()->Print("=================================================\n");
    GSignal()->MallocSigAction("SIGNAL");
    GSignal()->MallocSigJmpBuf("SIGNAL");
    //GSignal()->SigFillSet("SIGNAL");
    GSignal()->InitSigAction("SIGNAL", GProcessTest_Callback, 0);
    //GSignal()->SigLongJmp("SIGNAL", 1);
    //GSignal()->SigSetJmp("SIGNAL", 1);
    GSignal()->SigAction("SIGNAL", SIGALRM);
    GAlarm()->Alarm(1);
    GMainLoop2()->Exec();
    GSignal()->FreeSigAction("SIGNAL");
    GSignal()->FreeSigJmpBuf("SIGNAL");
    GConsole()->Print("=================================================\n");
}
//===============================================
