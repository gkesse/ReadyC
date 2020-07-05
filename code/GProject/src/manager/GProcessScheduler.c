//===============================================
#include "GProcessScheduler.h"
#include "GScheduler.h"
#include "GConsole.h"
#include "GLog.h"
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
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessScheduler_Run");
    //GLog()->Write("#================================================");
	GConsole()->Print("=================================================\n");
	GConsole()->Print("Je suis un ordonnanceur cooperatif [ Scheduler ]\n");
	GConsole()->Print("Je suis constitue d'un mode idle [ economie d'energie ]\n");
	GConsole()->Print("=================================================\n");
	GConsole()->Print("J'initialise le scheduler\n");
	GScheduler()->Init(1000); // Je cadence l'ordonnacement a une freq de 1ms
	GConsole()->Print("Je demarre le scheduler\n");
	GScheduler()->Start();
	GConsole()->Print("J'ajoute une tache au scheduler\n");
	GScheduler()->AddTask(GProcessScheduler_Task, 0, 200); // Je me repete chaque 200ms
	GConsole()->Print("Je passe le scheduler en mode IDLE\n");
	GScheduler()->MainLoop();
    GConsole()->Print("=================================================\n");
}
//===============================================
static void GProcessScheduler_Task() {
	GConsole()->Print("Je suis une tache 200ms...\n");
}
//===============================================
