//===============================================
#include "GProcessKernel.h"
#include "GKernelConnect.h"
#include "GKernelMenu.h"
#include "GKernelDashboard.h"
#include "GScheduler.h"
#include "GConsole.h"
#include "GLog.h"
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
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessKernel_Run");
    //GLog()->Write("#================================================");
	GScheduler()->Init(1000);
	GScheduler()->Start();
	GScheduler()->AddTask(GKernelConnect()->Update, 0, 200);
	GScheduler()->AddTask(GKernelMenu()->Update, 1, 200);
	GScheduler()->AddTask(GKernelDashboard()->Update, 3, 1000);
	GScheduler()->MainLoop();
}
//===============================================
