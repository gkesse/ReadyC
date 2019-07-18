//===============================================
#include "GProcessThread.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessThreadO = 0;
//===============================================
static void GProcessThread_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessThread_New() {
    GProcessO* lParent = GProcess_New();
    GProcessThreadO* lChild = (GProcessThreadO*)malloc(sizeof(GProcessThreadO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessThread_Delete;
    lParent->Run = GProcessThread_Run;
    return lParent;
}
//===============================================
void GProcessThread_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessThreadO);
    m_GProcessThreadO = 0;
}
//===============================================
GProcessO* GProcessThread() {
    if(m_GProcessThreadO == 0) {
        m_GProcessThreadO = GProcessThread_New();
    }
    return m_GProcessThreadO;
}
//===============================================
static void GProcessThread_Run(int argc, char** argv) {
	int lInt = 567;
	char* lString = "Bonjour tout le monde";
	GConsole()->Print("Entier decimal: [ %d ]\n", lInt);
	GConsole()->Print("Entier octal: [ %o ]\n", lInt);
	GConsole()->Print("Entier hexadecimal: [ %X ]\n", lInt);
	GConsole()->Print("Chaine: [ %s ]\n", lString);
}
//===============================================
