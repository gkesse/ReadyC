//===============================================
#include "GProcessTest.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef int* GINT_PTR;
typedef char* GCHAR_PTR;
//===============================================
GDECLARE_LIST(GINT_PTR, GProcessTest_GINT_PTR)
GDEFINE_LIST(GINT_PTR, GProcessTest_GINT_PTR)
//===============================================
GDECLARE_LIST(GCHAR_PTR, GProcessTest_GCHAR_PTR)
GDEFINE_LIST(GCHAR_PTR, GProcessTest_GCHAR_PTR)
#endif
//===============================================
static GProcessO* m_GProcessTestO = 0;
//===============================================
static void GProcessTest_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessTest_New() {
	GProcessO* lParent = GProcess_New();
	GProcessTestO* lChild = (GProcessTestO*)malloc(sizeof(GProcessTestO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessTest_Delete;
	lParent->Run = GProcessTest_Run;
	return lParent;
}
//===============================================
void GProcessTest_Delete() {
	GProcess_Delete(m_GProcessTestO);
	m_GProcessTestO = 0;
}
//===============================================
GProcessO* GProcessTest() {
	if(m_GProcessTestO == 0) {
		m_GProcessTestO = GProcessTest_New();
	}
	return m_GProcessTestO;
}
//===============================================
static void GProcessTest_Run(int argc, char** argv) {
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis une liste\n");
    GConsole()->Print("=================================================\n");

    GConsole()->Print("=================================================\n");
}
//===============================================
