//===============================================
#include "GProcessMutex.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessMutexO = 0;
//===============================================
static void GProcessMutex_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessMutex_New() {
    GProcessO* lParent = GProcess_New();
    GProcessMutexO* lChild = (GProcessMutexO*)malloc(sizeof(GProcessMutexO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessMutex_Delete;
    lParent->Run = GProcessMutex_Run;
    return lParent;
}
//===============================================
void GProcessMutex_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessMutexO);
    m_GProcessMutexO = 0;
}
//===============================================
GProcessO* GProcessMutex() {
    if(m_GProcessMutexO == 0) {
        m_GProcessMutexO = GProcessMutex_New();
    }
    return m_GProcessMutexO;
}
//===============================================
static void GProcessMutex_Run(int argc, char** argv) {
	int lInt = 567;
	char* lString = "Bonjour tout le monde";
	GConsole()->Print("Entier decimal: [ %d ]\n", lInt);
	GConsole()->Print("Entier octal: [ %o ]\n", lInt);
	GConsole()->Print("Entier hexadecimal: [ %X ]\n", lInt);
	GConsole()->Print("Chaine: [ %s ]\n", lString);
}
//===============================================
