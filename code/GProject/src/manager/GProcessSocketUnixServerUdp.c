//===============================================
#include "GProcessSocketUnixServerUdp.h"
#include "GSocket2.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSocketUnixServerUdpO = 0;
//===============================================
static void GProcessSocketUnixServerUdp_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketUnixServerUdp_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketUnixServerUdpO* lChild = (GProcessSocketUnixServerUdpO*)malloc(sizeof(GProcessSocketUnixServerUdpO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketUnixServerUdp_Delete;
	lParent->Run = GProcessSocketUnixServerUdp_Run;
	return lParent;
}
//===============================================
void GProcessSocketUnixServerUdp_Delete() {
	GProcess_Delete(m_GProcessSocketUnixServerUdpO);
	m_GProcessSocketUnixServerUdpO = 0;
}
//===============================================
GProcessO* GProcessSocketUnixServerUdp() {
	if(m_GProcessSocketUnixServerUdpO == 0) {
		m_GProcessSocketUnixServerUdpO = GProcessSocketUnixServerUdp_New();
	}
	return m_GProcessSocketUnixServerUdpO;
}
//===============================================
static void GProcessSocketUnixServerUdp_Run(int argc, char** argv) {
	GSocket2()->MallocSocket("SERVER");
	GSocket2()->MallocAddress("SERVER");
	GSocket2()->MallocAddress("CLIENT");
    
	GSocket2()->Socket("SERVER", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_SOCK_DGRAM, 0);
	GSocket2()->AddressInt("SERVER", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_INADDR_ANY, 5566);
	GSocket2()->Bind("SERVER", "SERVER");
    
    char lMessage[256];
    
	while(1) {
		GSocket2()->RecvFrom("SERVER", "CLIENT", lMessage, 255, 0);
        GConsole()->Print("%s\n", lMessage);
		GSocket2()->SendTo("SERVER", "CLIENT", "SERVER, Bonjour tout le monde", 0, 0);
	}
    
	GSocket2()->Close("SERVER");
	GSocket2()->FreeSocket("SERVER");
	GSocket2()->FreeAddress("SERVER");
	GSocket2()->FreeAddress("CLIENT");
}
//===============================================
