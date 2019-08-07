//===============================================
#include "GProcessTimer.h"
#include "GProcessTimer.h"
//===============================================
static GProcessO* m_GProcessTimerO = 0;
//===============================================
static void GProcessTimer_Run(int argc, char** argv);
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

}
//===============================================
