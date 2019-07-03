//===============================================
#include "GProcessSoapServer.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSoapServerO = 0;
//===============================================
static void GProcessSoapServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSoapServer_New() {
    GProcessO* lParent = GProcess_New();
    GProcessSoapServerO* lChild = (GProcessSoapServerO*)malloc(sizeof(GProcessSoapServerO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessSoapServer_Delete;
    lParent->Run = GProcessSoapServer_Run;
    return lParent;
}
//===============================================
void GProcessSoapServer_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSoapServerO);
	m_GProcessSoapServerO = 0;
}
//===============================================
GProcessO* GProcessSoapServer() {
    if(m_GProcessSoapServerO == 0) {
        m_GProcessSoapServerO = GProcessSoapServer_New();
    }
    return m_GProcessSoapServerO;
}
//===============================================
static void GProcessSoapServer_Run(int argc, char** argv) {
	GConsole()->Print("[ GSoap ] Server Start...\n");
}
//===============================================
