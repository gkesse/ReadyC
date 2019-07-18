//===============================================
#include "GProcessDbusClient.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessDbusClientO = 0;
//===============================================
static void GProcessDbusClient_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessDbusClient_New() {
    GProcessO* lParent = GProcess_New();
    GProcessDbusClientO* lChild = (GProcessDbusClientO*)malloc(sizeof(GProcessDbusClientO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessDbusClient_Delete;
    lParent->Run = GProcessDbusClient_Run;
    return lParent;
}
//===============================================
void GProcessDbusClient_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessDbusClientO);
    m_GProcessDbusClientO = 0;
}
//===============================================
GProcessO* GProcessDbusClient() {
    if(m_GProcessDbusClientO == 0) {
        m_GProcessDbusClientO = GProcessDbusClient_New();
    }
    return m_GProcessDbusClientO;
}
//===============================================
static void GProcessDbusClient_Run(int argc, char** argv) {
	int lInt = 567;
	char* lString = "Bonjour tout le monde";
	GConsole()->Print("Entier decimal: [ %d ]\n", lInt);
	GConsole()->Print("Entier octal: [ %o ]\n", lInt);
	GConsole()->Print("Entier hexadecimal: [ %X ]\n", lInt);
	GConsole()->Print("Chaine: [ %s ]\n", lString);
}
//===============================================
