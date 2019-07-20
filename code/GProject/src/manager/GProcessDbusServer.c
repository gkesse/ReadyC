//===============================================
#include "GProcessDbusServer.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessDbusServerO = 0;
//===============================================
static void GProcessDbusServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessDbusServer_New() {
    GProcessO* lParent = GProcess_New();
    GProcessDbusServerO* lChild = (GProcessDbusServerO*)malloc(sizeof(GProcessDbusServerO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessDbusServer_Delete;
    lParent->Run = GProcessDbusServer_Run;
    return lParent;
}
//===============================================
void GProcessDbusServer_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessDbusServerO);
    m_GProcessDbusServerO = 0;
}
//===============================================
GProcessO* GProcessDbusServer() {
    if(m_GProcessDbusServerO == 0) {
        m_GProcessDbusServerO = GProcessDbusServer_New();
    }
    return m_GProcessDbusServerO;
}
//===============================================
static void GProcessDbusServer_Run(int argc, char** argv) {

}
//===============================================
