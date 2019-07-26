//===============================================
#include "GProcessSocketServer.h"
#include "GSocket2.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSocketServerO = 0;
//===============================================
static void GProcessSocketServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketServer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketServerO* lChild = (GProcessSocketServerO*)malloc(sizeof(GProcessSocketServerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketServer_Delete;
	lParent->Run = GProcessSocketServer_Run;
	return lParent;
}
//===============================================
void GProcessSocketServer_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSocketServerO);
	m_GProcessSocketServerO = 0;
}
//===============================================
GProcessO* GProcessSocketServer() {
	if(m_GProcessSocketServerO == 0) {
		m_GProcessSocketServerO = GProcessSocketServer_New();
	}
	return m_GProcessSocketServerO;
}
//===============================================
static void GProcessSocketServer_Run(int argc, char** argv) {

}
//===============================================
