//===============================================
#include "GProcessCgi.h"
#include "GConfig.h"
//===============================================
static GProcessO* m_GProcessCgiO = 0;
//===============================================
static void GProcessCgi_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessCgi_New() {
	GProcessO* lParent = GProcess_New();
	GProcessCgiO* lChild = (GProcessCgiO*)malloc(sizeof(GProcessCgiO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessCgi_Delete;
	lParent->Run = GProcessCgi_Run;
	return lParent;
}
//===============================================
void GProcessCgi_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessCgiO);
	m_GProcessCgiO = 0;
}
//===============================================
GProcessO* GProcessCgi() {
	if(m_GProcessCgiO == 0) {
		m_GProcessCgiO = GProcessCgi_New();
	}
	return m_GProcessCgiO;
}
//===============================================
static void GProcessCgi_Run(int argc, char** argv) {
	printf("Content-Type: text/plain;charset=us-ascii\n\n");
	printf("Hello world\n\n");
}
//===============================================
