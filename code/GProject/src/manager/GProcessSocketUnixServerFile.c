//===============================================
#include "GProcessSocketUnixServerFile.h"
#include "GSocket2.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSocketUnixServerFileO = 0;
//===============================================
static void GProcessSocketUnixServerFile_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketUnixServerFile_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketUnixServerFileO* lChild = (GProcessSocketUnixServerFileO*)malloc(sizeof(GProcessSocketUnixServerFileO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketUnixServerFile_Delete;
	lParent->Run = GProcessSocketUnixServerFile_Run;
	return lParent;
}
//===============================================
void GProcessSocketUnixServerFile_Delete() {
	GProcess_Delete(m_GProcessSocketUnixServerFileO);
	m_GProcessSocketUnixServerFileO = 0;
}
//===============================================
GProcessO* GProcessSocketUnixServerFile() {
	if(m_GProcessSocketUnixServerFileO == 0) {
		m_GProcessSocketUnixServerFileO = GProcessSocketUnixServerFile_New();
	}
	return m_GProcessSocketUnixServerFileO;
}
//===============================================
static void GProcessSocketUnixServerFile_Run(int argc, char** argv) {
	GSocket2()->MallocSocket("SERVER");
	GSocket2()->MallocAddress("SERVER");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("CLIENT");
    
	GSocket2()->Socket("SERVER", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_SOCK_STREAM, GSOCKET2_INIT_IPPROTO_TCP);
	GSocket2()->AddressInt("SERVER", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_INADDR_ANY, 5566);
	GSocket2()->Bind("SERVER", "SERVER");
	GSocket2()->Listen("SERVER", 5);
    
    char lFilename[256];
    
	while(1) {
		GSocket2()->Accept("SERVER", "CLIENT", "CLIENT");
		GSocket2()->Read("CLIENT", lFilename, 256);
		GConsole()->Print("Filename : %s", lFilename);
		GSocket2()->Close("CLIENT");
	}
    
	GSocket2()->Close("SERVER");
    
	GSocket2()->FreeSocket("SERVER");
	GSocket2()->FreeSocket("CLIENT");
	GSocket2()->FreeAddress("SERVER");
	GSocket2()->FreeAddress("CLIENT");
}
//===============================================
