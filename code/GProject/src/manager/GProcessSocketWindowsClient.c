//===============================================
#include "GProcessSocketWindowsClient.h"
#include "GSocket2.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
static GProcessO* m_GProcessSocketWindowsClientO = 0;
//===============================================
static void GProcessSocketWindowsClient_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketWindowsClient_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketWindowsClientO* lChild = (GProcessSocketWindowsClientO*)malloc(sizeof(GProcessSocketWindowsClientO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketWindowsClient_Delete;
	lParent->Run = GProcessSocketWindowsClient_Run;
	return lParent;
}
//===============================================
void GProcessSocketWindowsClient_Delete() {
	GProcess_Delete(m_GProcessSocketWindowsClientO);
	m_GProcessSocketWindowsClientO = 0;
}
//===============================================
GProcessO* GProcessSocketWindowsClient() {
	if(m_GProcessSocketWindowsClientO == 0) {
		m_GProcessSocketWindowsClientO = GProcessSocketWindowsClient_New();
	}
	return m_GProcessSocketWindowsClientO;
}
//===============================================
static void GProcessSocketWindowsClient_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessSocketWindowsClient_Run");
    //GLog()->Write("#================================================");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocData("CLIENT");
	GSocket2()->MallocAddress("SERVER");

	GSocket2()->Start("CLIENT", 2, 2);
	GSocket2()->Socket("CLIENT", GSOCKET2_INIT_AF_INET , GSOCKET2_INIT_SOCK_STREAM, 0);
	GSocket2()->AddressChar("SERVER", GSOCKET2_INIT_AF_INET, "127.0.0.1", 5566);
	GSocket2()->Connect("CLIENT", "SERVER");
	char lMessage[255];
	GSocket2()->Recv("CLIENT", lMessage, 254);
	GConsole()->Print("%s\n", lMessage);
	GSocket2()->Close("CLIENT");
	GSocket2()->Clean();
	GSocket2()->FreeSocket("CLIENT");
	GSocket2()->FreeData("CLIENT");
	GSocket2()->FreeAddress("SERVER");
}
//===============================================
#endif
//===============================================
