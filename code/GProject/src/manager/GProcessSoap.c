//===============================================
#include "GProcessSoap.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSoapO = 0;
//===============================================
static void GProcessSoap_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSoap_New() {
    GProcessO* lParent = GProcess_New();
    GProcessSoapO* lChild = (GProcessSoapO*)malloc(sizeof(GProcessSoapO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessSoap_Delete;
    lParent->Run = GProcessSoap_Run;
    return lParent;
}
//===============================================
void GProcessSoap_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSoapO);
	m_GProcessSoapO = 0;
}
//===============================================
GProcessO* GProcessSoap() {
    if(m_GProcessSoapO == 0) {
        m_GProcessSoapO = GProcessSoap_New();
    }
    return m_GProcessSoapO;
}
//===============================================
static void GProcessSoap_Run(int argc, char** argv) {
	GConsole()->Print("[ GSoap ] Start...\n");
}
//===============================================
