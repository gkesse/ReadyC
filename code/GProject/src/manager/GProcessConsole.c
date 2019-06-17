//===============================================
#include "GProcessConsole.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessConsoleO = 0;
//===============================================
static void GProcessConsole_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessConsole_New() {
    GProcessO* lParent = GProcess_New();
    GProcessConsoleO* lChild = (GProcessConsoleO*)malloc(sizeof(GProcessConsoleO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessConsole_Delete;
    lParent->Run = GProcessConsole_Run;
    return lParent;
}
//===============================================
void GProcessConsole_Delete(GProcessO* obj) {
    GProcess_Delete(obj);
}
//===============================================
GProcessO* GProcessConsole() {
    if(m_GProcessConsoleO == 0) {
        m_GProcessConsoleO = GProcessConsole_New();
    }
    return m_GProcessConsoleO;
}
//===============================================
static void GProcessConsole_Run(int argc, char** argv) {
	int lInt = 567;
	char* lString = "Bonjour tout le monde";
	GConsole()->Print("Entier decimal: [ %d ]\n", lInt);
	GConsole()->Print("Entier octal: [ %o ]\n", lInt);
	GConsole()->Print("Entier hexadecimal: [ %X ]\n", lInt);
	GConsole()->Print("Chaine: [ %s ]\n", lString);
}
//===============================================
