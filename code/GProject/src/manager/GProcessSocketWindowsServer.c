//===============================================
#include "GProcessSocketWindowsServer.h"
#include "GSocket2.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
static GProcessO* m_GProcessSocketWindowsServerO = 0;
//===============================================
static void GProcessSocketWindowsServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketWindowsServer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketWindowsServerO* lChild = (GProcessSocketWindowsServerO*)malloc(sizeof(GProcessSocketWindowsServerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketWindowsServer_Delete;
	lParent->Run = GProcessSocketWindowsServer_Run;
	return lParent;
}
//===============================================
void GProcessSocketWindowsServer_Delete() {
	GProcess_Delete(m_GProcessSocketWindowsServerO);
	m_GProcessSocketWindowsServerO = 0;
}
//===============================================
GProcessO* GProcessSocketWindowsServer() {
	if(m_GProcessSocketWindowsServerO == 0) {
		m_GProcessSocketWindowsServerO = GProcessSocketWindowsServer_New();
	}
	return m_GProcessSocketWindowsServerO;
}
//===============================================
static void GProcessSocketWindowsServer_Run(int argc, char** argv) {
#if defined(__WIN32)
    GLog()->Write("#================================================");
    GLog()->Write("# Execution de la fonction : GProcessSocketWindowsServer_Run");
    GLog()->Write("#================================================");
	GSocket2()->MallocSocket("SERVER");
	GSocket2()->MallocAddress("SERVER");
	GSocket2()->MallocData("SERVER");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("CLIENT");

	GSocket2()->Start("SERVER", 2, 2);
	GSocket2()->Socket("SERVER", GSOCKET2_INIT_AF_INET , GSOCKET2_INIT_SOCK_STREAM, 0);

	GSocket2()->Bind("SERVER", "SERVER");
	GSocket2()->Listen("SERVER", 5);

	while(1) {
		GSocket2()->Accept("SERVER", "CLIENT", "CLIENT");
		GSocket2()->Send("CLIENT", "Bonjour tout le monde", 0);
		GSocket2()->Close("CLIENT");
	}

	GSocket2()->Close("SERVER");
	GSocket2()->Clean();
	GSocket2()->FreeSocket("SERVER");
	GSocket2()->FreeAddress("SERVER");
	GSocket2()->FreeData("SERVER");
#endif
}
//===============================================
