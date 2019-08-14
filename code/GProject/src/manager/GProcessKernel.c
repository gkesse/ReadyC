//===============================================
#include "GProcessKernel.h"
#include "GKernelMenu.h"
#include "GKernelDashboard.h"
#include "GScheduler.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessKernelO = 0;
//===============================================
static void GProcessKernel_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessKernel_New() {
	GProcessO* lParent = GProcess_New();
	GProcessKernelO* lChild = (GProcessKernelO*)malloc(sizeof(GProcessKernelO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessKernel_Delete;
	lParent->Run = GProcessKernel_Run;
	return lParent;
}
//===============================================
void GProcessKernel_Delete() {
	GProcess_Delete(m_GProcessKernelO);
	m_GProcessKernelO = 0;
}
//===============================================
GProcessO* GProcessKernel() {
	if(m_GProcessKernelO == 0) {
		m_GProcessKernelO = GProcessKernel_New();
	}
	return m_GProcessKernelO;
}
//===============================================
static void GProcessKernel_Run(int argc, char** argv) {
	GScheduler()->Init(1000);
	GScheduler()->Start();
	GScheduler()->AddTask(GKernelMenu_Update, 0, 200);
	GScheduler()->AddTask(GKernelDashboard_Update, 1, 1000);
	GScheduler()->MainLoop();
}
//===============================================
