//===============================================
#include "GProcessFork.h"
#include "GConsole.h"
#include "GThread2.h"
#include "GSleep.h"
//===============================================
static GProcessO* m_GProcessForkO = 0;
//===============================================
static void GProcessFork_Run(int argc, char** argv);
//===============================================
static void GProcessFork_Parent();
static void GProcessFork_Child();
//===============================================
GProcessO* GProcessFork_New() {
	GProcessO* lParent = GProcess_New();
	GProcessForkO* lChild = (GProcessForkO*)malloc(sizeof(GProcessForkO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessFork_Delete;
	lParent->Run = GProcessFork_Run;
	return lParent;
}
//===============================================
void GProcessFork_Delete() {
	GProcess_Delete(m_GProcessForkO);
	m_GProcessForkO = 0;
}
//===============================================
GProcessO* GProcessFork() {
	if(m_GProcessForkO == 0) {
		m_GProcessForkO = GProcessFork_New();
	}
	return m_GProcessForkO;
}
//===============================================
static void GProcessFork_Run(int argc, char** argv) {
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je teste l'utilisation de fork()\n");
    GConsole()->Print("=================================================\n");
    int lPid = GProcess()->Fork();
    if(lPid == 0) GProcessFork_Child();
    else GProcessFork_Parent();
    GProcess()->Wait();
}
//===============================================
static void GProcessFork_Parent() {
    GConsole()->Print("Je suis le Parent\n");
}
//===============================================
static void GProcessFork_Child() {
    GConsole()->Print("Je suis un Fils\n");
}
//===============================================
