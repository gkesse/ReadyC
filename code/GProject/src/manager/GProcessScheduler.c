//===============================================
#include "GProcessScheduler.h"
#include "GScheduler.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSchedulerO = 0;
//===============================================
static void GProcessScheduler_Run(int argc, char** argv);
//===============================================
static void GProcessScheduler_Task(void* params);
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
	GConsole()->Print("Je suis un ordonnanceur cooperatif\n");
	GConsole()->Print("=================================================\n");
	GScheduler()->Init(10);
	GScheduler()->AddTask(GProcessScheduler_Task, 0, 1000, 0);
    GConsole()->Print("=================================================\n");
}
//===============================================
static void GProcessScheduler_Task(void* params) {
	GConsole()->Print("Je suis une tache\n");
}
//===============================================
