//===============================================
#include "GProcessSocketUnixClient.h"
#include "GSocket2.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
static GProcessO* m_GProcessSocketUnixClientO = 0;
//===============================================
static void GProcessSocketUnixClient_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketUnixClient_New() {
    GProcessO* lParent = GProcess_New();
    GProcessSocketUnixClientO* lChild = (GProcessSocketUnixClientO*)malloc(sizeof(GProcessSocketUnixClientO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessSocketUnixClient_Delete;
    lParent->Run = GProcessSocketUnixClient_Run;
    return lParent;
}
//===============================================
void GProcessSocketUnixClient_Delete() {
	GProcess_Delete(m_GProcessSocketUnixClientO);
	m_GProcessSocketUnixClientO = 0;
}
//===============================================
GProcessO* GProcessSocketUnixClient() {
    if(m_GProcessSocketUnixClientO == 0) {
        m_GProcessSocketUnixClientO = GProcessSocketUnixClient_New();
    }
    return m_GProcessSocketUnixClientO;
}
//===============================================
static void GProcessSocketUnixClient_Run(int argc, char** argv) {
    GLog()->Write("#================================================");
    GLog()->Write("# Execution de la fonction : GProcessSocketUnixClient_Run");
    GLog()->Write("#================================================");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("SERVER");
    
	GSocket2()->Socket("CLIENT", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_SOCK_STREAM, GSOCKET2_INIT_IPPROTO_TCP);
	GSocket2()->AddressChar("SERVER", GSOCKET2_INIT_AF_INET, "127.0.0.1", 5566);
	GSocket2()->Connect("CLIENT", "SERVER");
    
	char lMessage[256];
    
	GSocket2()->Read("CLIENT", lMessage, 256);
	GConsole()->Print("%s\n", lMessage);
	GSocket2()->Write("CLIENT", "CLIENT: Bonjour tout le monde", 0);
    
	GSocket2()->Close("CLIENT");
    
	GSocket2()->FreeSocket("CLIENT");
	GSocket2()->FreeAddress("SERVER");
}
//===============================================
