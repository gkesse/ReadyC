//===============================================
#include "GProcessRpcClient.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
static GProcessO* m_GProcessRpcClientO = 0;
//===============================================
static void GProcessRpcClient_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessRpcClient_New() {
    GProcessO* lParent = GProcess_New();
    GProcessRpcClientO* lChild = (GProcessRpcClientO*)malloc(sizeof(GProcessRpcClientO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessRpcClient_Delete;
    lParent->Run = GProcessRpcClient_Run;
    return lParent;
}
//===============================================
void GProcessRpcClient_Delete() {
	GProcess_Delete(m_GProcessRpcClientO);
    m_GProcessRpcClientO = 0;
}
//===============================================
GProcessO* GProcessRpcClient() {
    if(m_GProcessRpcClientO == 0) {
        m_GProcessRpcClientO = GProcessRpcClient_New();
    }
    return m_GProcessRpcClientO;
}
//===============================================
static void GProcessRpcClient_Run(int argc, char** argv) {
    GLog()->Write("#================================================");
    GLog()->Write("# Execution de la fonction : GProcessRpcClient_Run");
    GLog()->Write("#================================================");
	int lInt = 567;
	char* lString = "Bonjour tout le monde";
	GConsole()->Print("Entier decimal: [ %d ]\n", lInt);
	GConsole()->Print("Entier octal: [ %o ]\n", lInt);
	GConsole()->Print("Entier hexadecimal: [ %X ]\n", lInt);
	GConsole()->Print("Chaine: [ %s ]\n", lString);
}
//===============================================
