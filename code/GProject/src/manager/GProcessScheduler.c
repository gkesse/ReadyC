//===============================================
#include "GProcessScheduler.h"
#include "GScheduler.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSchedulerO = 0;
//===============================================
static void GProcessScheduler_Run(int argc, char** argv);
//===============================================
static void GProcessScheduler_Task();
//===============================================
GProcessO* GProcessScheduler_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSchedulerO* lChild = (GProcessSchedulerO*)malloc(sizeof(GProcessSchedulerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessScheduler_Delete;
	lParent->Run = GProcessScheduler_Run;
	return lParent;
}
//===============================================
void GProcessScheduler_Delete() {
	GProcess_Delete(m_GProcessSchedulerO);
	m_GProcessSchedulerO = 0;
}
//===============================================
GProcessO* GProcessScheduler() {
	if(m_GProcessSchedulerO == 0) {
		m_GProcessSchedulerO = GProcessScheduler_New();
	}
	return m_GProcessSchedulerO;
}
//===============================================
static void GProcessScheduler_Run(int argc, char** argv) {
	GConsole()->Print("=================================================\n");
	GConsole()->Print("Je suis un ordonnanceur cooperatif [ Scheduler ]\n");
	GConsole()->Print("=================================================\n");
	GConsole()->Print("J'initialise le scheduler\n");
	GScheduler()->Init(0.1);
	GConsole()->Print("Je demarre le scheduler\n");
	GScheduler()->Start();
	GConsole()->Print("J'ajoute une tache au scheduler\n");
	GScheduler()->AddTask(GProcessScheduler_Task, 0, 1);
	GConsole()->Print("Je passe le scheduler en mode IDLE\n");
	GScheduler()->MainLoop();
    GConsole()->Print("=================================================\n");
}
//===============================================
static void GProcessScheduler_Task() {
	GConsole()->Print("Je suis une tache\n");
}
//===============================================
