//===============================================
#include "GProcessSocketUnixClient.h"
#include "GSocket2.h"
#include "GConsole.h"
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
#if defined(__unix)
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("SERVER");
	GSocket2()->Socket("CLIENT", AF_INET, SOCK_STREAM, IPPROTO_TCP);
	GSocket2()->AddressChar("SERVER", AF_INET, "127.0.0.1", 5566);
	GSocket2()->Connect("CLIENT", "SERVER");
	char lMessage[255];
	GSocket2()->Read("CLIENT", lMessage, 254);
	GConsole()->Print("%s\n", lMessage);
	GSocket2()->Close("CLIENT");
	GSocket2()->FreeSocket("CLIENT");
	GSocket2()->FreeAddress("SERVER");
#endif
}
//===============================================
