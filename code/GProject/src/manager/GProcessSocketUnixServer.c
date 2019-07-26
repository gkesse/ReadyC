//===============================================
#include "GProcessSocketUnixServer.h"
#include "GSocket2.h"
#include "GConsole.h"
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
	// Delete All Attributes Before
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
#if defined(__unix)
	GSocket2()->MallocSocket("SERVER");
	GSocket2()->MallocAddress("SERVER");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("CLIENT");
	GSocket2()->Socket("SERVER", AF_INET, SOCK_STREAM, IPPROTO_TCP);
	GSocket2()->AddressInt("SERVER", AF_INET, INADDR_ANY, 5566);
	GSocket2()->Bind("SERVER", "SERVER");
	GSocket2()->Listen("SERVER", 5);
	while(1) {
		GSocket2()->Accept("SERVER", "CLIENT", "CLIENT");
		GSocket2()->Write("CLIENT", "BONJR", 0);
		GSocket2()->Close("CLIENT");
	}
	GSocket2()->Close("SERVER");
	GSocket2()->FreeSocket("SERVER");
	GSocket2()->FreeSocket("CLIENT");
	GSocket2()->FreeAddress("SERVER");
	GSocket2()->FreeAddress("CLIENT");
#endif
}
//===============================================
