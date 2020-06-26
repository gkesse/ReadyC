//===============================================
#include "GProcessSocketUnixServer.h"
#include "GSocket2.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
static GProcessO* m_GProcessSocketUnixServerO = 0;
//===============================================
static void GProcessSocketUnixServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketUnixServer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketUnixServerO* lChild = (GProcessSocketUnixServerO*)malloc(sizeof(GProcessSocketUnixServerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketUnixServer_Delete;
	lParent->Run = GProcessSocketUnixServer_Run;
	return lParent;
}
//===============================================
void GProcessSocketUnixServer_Delete() {
	GProcess_Delete(m_GProcessSocketUnixServerO);
	m_GProcessSocketUnixServerO = 0;
}
//===============================================
GProcessO* GProcessSocketUnixServer() {
	if(m_GProcessSocketUnixServerO == 0) {
		m_GProcessSocketUnixServerO = GProcessSocketUnixServer_New();
	}
	return m_GProcessSocketUnixServerO;
}
//===============================================
static void GProcessSocketUnixServer_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessSocketUnixServer_Run");
    //GLog()->Write("#================================================");
	GSocket2()->MallocSocket("SERVER");
	GSocket2()->MallocAddress("SERVER");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("CLIENT");
    
	GSocket2()->Socket("SERVER", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_SOCK_STREAM, GSOCKET2_INIT_IPPROTO_TCP);
	GSocket2()->AddressInt("SERVER", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_INADDR_ANY, 5566);
	GSocket2()->Bind("SERVER", "SERVER");
	GSocket2()->Listen("SERVER", 5);
    
    char lMessage[256];
    
	while(1) {
		GSocket2()->Accept("SERVER", "CLIENT", "CLIENT");
		GSocket2()->Write("CLIENT", "SERVER: Bonjour tout le monde", 0);
        GSocket2()->Read("CLIENT", lMessage, 256);
        GConsole()->Print("%s\n", lMessage);
		GSocket2()->Close("CLIENT");
	}
    
	GSocket2()->Close("SERVER");
    
	GSocket2()->FreeSocket("SERVER");
	GSocket2()->FreeSocket("CLIENT");
	GSocket2()->FreeAddress("SERVER");
	GSocket2()->FreeAddress("CLIENT");
}
//===============================================
#endif
//===============================================
