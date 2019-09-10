//===============================================
#include "GProcessAlarmSignal.h"
#include "GSched.h"
#include "GAlarm.h"
#include "GPause.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessAlarmSignalO = 0;
//===============================================
static void GProcessAlarmSignal_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessAlarmSignal_New() {
	GProcessO* lParent = GProcess_New();
	GProcessAlarmSignalO* lChild = (GProcessAlarmSignalO*)malloc(sizeof(GProcessAlarmSignalO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessAlarmSignal_Delete;
	lParent->Run = GProcessAlarmSignal_Run;
	return lParent;
}
//===============================================
void GProcessAlarmSignal_Delete() {
	GProcess_Delete(m_GProcessAlarmSignalO);
	m_GProcessAlarmSignalO = 0;
}
//===============================================
GProcessO* GProcessAlarmSignal() {
	if(m_GProcessAlarmSignalO == 0) {
		m_GProcessAlarmSignalO = GProcessAlarmSignal_New();
	}
	return m_GProcessAlarmSignalO;
}
//===============================================
static void GProcessAlarmSignal_Run(int argc, char** argv) {
    GConsole()->Print("=================================================\n");
    GConsole()->Print("J'envoie un signal alarm apres (x) secondes\n");
    GConsole()->Print("=================================================\n");
    GSched()->MallocSchedParam("SCHED");
    GSched()->InitSchedParam("SCHED", 99);
    GSched()->SetScheduler("SCHED", 0, GSCHED_SCHED_FIFO);
    GAlarm()->Alarm(5);
    GSched()->FreeSchedParam("SCHED");
    GPause()->Pause();
    GConsole()->Print("=================================================\n");
}
//===============================================
