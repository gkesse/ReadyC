//===============================================
#include "GProcessScheduler.h"
#include "GConsole.h"
#include "GScheduler.h"
//===============================================
static GProcessO* m_GProcessSchedulerO = 0;
//===============================================
static void GProcessScheduler_Run(int argc, char** argv);
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
	GConsole()->Print("[ GScheduler ] Start...\n ");
}
//===============================================
