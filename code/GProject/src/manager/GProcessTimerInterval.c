//===============================================
#include "GProcessTimerInterval.h"
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <sys/time.h>
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
static void GProcessTimerInterval_Run(int argc, char** argv) {

}
//===============================================
