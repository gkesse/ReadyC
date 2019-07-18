//===============================================
#include "GProcessRpcServer.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessRpcServerO = 0;
//===============================================
static void GProcessRpcServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessRpcServer_New() {
    GProcessO* lParent = GProcess_New();
    GProcessRpcServerO* lChild = (GProcessRpcServerO*)malloc(sizeof(GProcessRpcServerO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessRpcServer_Delete;
    lParent->Run = GProcessRpcServer_Run;
    return lParent;
}
//===============================================
void GProcessRpcServer_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessRpcServerO);
    m_GProcessRpcServerO = 0;
}
//===============================================
GProcessO* GProcessRpcServer() {
    if(m_GProcessRpcServerO == 0) {
        m_GProcessRpcServerO = GProcessRpcServer_New();
    }
    return m_GProcessRpcServerO;
}
//===============================================
static void GProcessRpcServer_Run(int argc, char** argv) {
	int lInt = 567;
	char* lString = "Bonjour tout le monde";
	GConsole()->Print("Entier decimal: [ %d ]\n", lInt);
	GConsole()->Print("Entier octal: [ %o ]\n", lInt);
	GConsole()->Print("Entier hexadecimal: [ %X ]\n", lInt);
	GConsole()->Print("Chaine: [ %s ]\n", lString);
}
//===============================================
