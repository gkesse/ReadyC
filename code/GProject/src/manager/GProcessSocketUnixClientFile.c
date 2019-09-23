//===============================================
#include "GProcessSocketUnixClientFile.h"
#include "GSocket2.h"
#include "GConsole.h"
#include "GLog.h"
#include "GFile2.h"
//===============================================
static GProcessO* m_GProcessSocketUnixClientFileO = 0;
//===============================================
static void GProcessSocketUnixClientFile_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketUnixClientFile_New() {
    GProcessO* lParent = GProcess_New();
    GProcessSocketUnixClientFileO* lChild = (GProcessSocketUnixClientFileO*)malloc(sizeof(GProcessSocketUnixClientFileO));

    lChild->m_parent = lParent; 

    lParent->m_child = lChild;
    lParent->Delete = GProcessSocketUnixClientFile_Delete;
    lParent->Run = GProcessSocketUnixClientFile_Run;
    return lParent;
}
//===============================================
void GProcessSocketUnixClientFile_Delete() {
	GProcess_Delete(m_GProcessSocketUnixClientFileO);
	m_GProcessSocketUnixClientFileO = 0;
}
//===============================================
GProcessO* GProcessSocketUnixClientFile() {
    if(m_GProcessSocketUnixClientFileO == 0) {
        m_GProcessSocketUnixClientFileO = GProcessSocketUnixClientFile_New();
    }
    return m_GProcessSocketUnixClientFileO;
}
//===============================================
static void GProcessSocketUnixClientFile_Run(int argc, char** argv) {
    GLog()->Write("#================================================");
    GLog()->Write("# Execution de la fonction : GProcessSocketUnixClientFile_Run");
    GLog()->Write("#================================================");
	GSocket2()->MallocSocket("CLIENT");
	GSocket2()->MallocAddress("SERVER");
    
    char lData[GSOCKET2_BUFFER_DATA];

	GSocket2()->Socket("CLIENT", GSOCKET2_INIT_AF_INET, GSOCKET2_INIT_SOCK_STREAM, GSOCKET2_INIT_IPPROTO_TCP);
	GSocket2()->AddressChar("SERVER", GSOCKET2_INIT_AF_INET, "127.0.0.1", 5566);
	GSocket2()->Connect("CLIENT", "SERVER");

	GSocket2()->Write("CLIENT", "Makefile", 0);
    GFile2()->Open("CLIENT", "data/recv/Makefile", "w");

    while(1) {
        int lReadBytes = GSocket2()->Read("CLIENT", lData, GSOCKET2_BUFFER_DATA);
        if(lReadBytes <= 0) break;
        GConsole()->Print("%s", lData);
        GFile2()->Write("CLIENT", lData, 0);
    }
    
	GFile2()->Close("CLIENT");
	GSocket2()->Close("CLIENT");
    
	GSocket2()->FreeSocket("CLIENT");
	GSocket2()->FreeAddress("SERVER");
}
//===============================================
