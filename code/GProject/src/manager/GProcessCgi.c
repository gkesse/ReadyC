//===============================================
#include "GProcessCgi.h"
#include "GConfig.h"
#include "GLog.h"
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
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessCgi_Run");
    //GLog()->Write("#================================================");
	printf("Content-Type: text/html;charset=utf-8\n\n");
	printf("<h1 style='color: red;'>[ GCgi ] Bonjour tout le monde</h1>\n\n");
}
//===============================================
