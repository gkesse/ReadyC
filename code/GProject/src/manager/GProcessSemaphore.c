//===============================================
#include "GProcessSemaphore.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
static GProcessO* m_GProcessSemaphoreO = 0;
//===============================================
static void GProcessSemaphore_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSemaphore_New() {
    GProcessO* lParent = GProcess_New();
    GProcessSemaphoreO* lChild = (GProcessSemaphoreO*)malloc(sizeof(GProcessSemaphoreO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessSemaphore_Delete;
    lParent->Run = GProcessSemaphore_Run;
    return lParent;
}
//===============================================
void GProcessSemaphore_Delete() {
	GProcess_Delete(m_GProcessSemaphoreO);
    m_GProcessSemaphoreO = 0;
}
//===============================================
GProcessO* GProcessSemaphore() {
    if(m_GProcessSemaphoreO == 0) {
        m_GProcessSemaphoreO = GProcessSemaphore_New();
    }
    return m_GProcessSemaphoreO;
}
//===============================================
static void GProcessSemaphore_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessSemaphore_Run");
    //GLog()->Write("#================================================");
	int lInt = 567;
	char* lString = "Bonjour tout le monde";
	GConsole()->Print("Entier decimal: [ %d ]\n", lInt);
	GConsole()->Print("Entier octal: [ %o ]\n", lInt);
	GConsole()->Print("Entier hexadecimal: [ %X ]\n", lInt);
	GConsole()->Print("Chaine: [ %s ]\n", lString);
}
//===============================================
