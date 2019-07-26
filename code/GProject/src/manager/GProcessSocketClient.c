//===============================================
#include "GProcessSocketClient.h"
#include "GSocket2.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSocketClientO = 0;
//===============================================
static void GProcessSocketClient_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketClient_New() {
    GProcessO* lParent = GProcess_New();
    GProcessSocketClientO* lChild = (GProcessSocketClientO*)malloc(sizeof(GProcessSocketClientO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessSocketClient_Delete;
    lParent->Run = GProcessSocketClient_Run;
    return lParent;
}
//===============================================
void GProcessSocketClient_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSocketClientO);
	m_GProcessSocketClientO = 0;
}
//===============================================
GProcessO* GProcessSocketClient() {
    if(m_GProcessSocketClientO == 0) {
        m_GProcessSocketClientO = GProcessSocketClient_New();
    }
    return m_GProcessSocketClientO;
}
//===============================================
static void GProcessSocketClient_Run(int argc, char** argv) {

}
//===============================================
