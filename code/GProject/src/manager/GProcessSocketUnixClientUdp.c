//===============================================
#include "GProcessSocketUnixClientUdp.h"
#include "GSocket2.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
static GProcessO* m_GProcessSocketUnixClientUdpO = 0;
//===============================================
static void GProcessSocketUnixClientUdp_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketUnixClientUdp_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketUnixClientUdpO* lChild = (GProcessSocketUnixClientUdpO*)malloc(sizeof(GProcessSocketUnixClientUdpO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketUnixClientUdp_Delete;
	lParent->Run = GProcessSocketUnixClientUdp_Run;
	return lParent;
}
//===============================================
void GProcessSocketUnixClientUdp_Delete() {
	GProcess_Delete(m_GProcessSocketUnixClientUdpO);
	m_GProcessSocketUnixClientUdpO = 0;
}
//===============================================
GProcessO* GProcessSocketUnixClientUdp() {
	if(m_GProcessSocketUnixClientUdpO == 0) {
		m_GProcessSocketUnixClientUdpO = GProcessSocketUnixClientUdp_New();
	}
	return m_GProcessSocketUnixClientUdpO;
}
//===============================================
static void GProcessSocketUnixClientUdp_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessSocketUnixClientUdp_Run");
    //GLog()->Write("#================================================");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("CLIENT");
	GSocket2()->MallocAddress("SERVER");
    
	GSocket2()->Socket("CLIENT", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_SOCK_DGRAM, 0);
	GSocket2()->AddressInt("CLIENT", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_INADDR_ANY, 0);
	GSocket2()->AddressChar("SERVER", GSOCKET2_INIT_AF_INET, "127.0.0.1", 5566);
	GSocket2()->Bind("CLIENT", "CLIENT");
    
    char lMessage[256];
    
    GSocket2()->SendTo("CLIENT", "SERVER", "CLIENT: Bonjour tout le monde", 0, 0);
    GSocket2()->RecvFrom("CLIENT", "SERVER", lMessage, 256, 0);
    GConsole()->Print("%s\n", lMessage);
    
	GSocket2()->Close("CLIENT");
	GSocket2()->FreeSocket("SERVER");
	GSocket2()->FreeAddress("SERVER");
	GSocket2()->FreeAddress("CLIENT");
}
//===============================================
#endif
//===============================================
