//===============================================
#include "GProcessGtk.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessGtkO = 0;
//===============================================
static void GProcessGtk_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessGtk_New() {
    GProcessO* lParent = GProcess_New();
    GProcessGtkO* lChild = (GProcessGtkO*)malloc(sizeof(GProcessGtkO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessGtk_Delete;
    lParent->Run = GProcessGtk_Run;
    return lParent;
}
//===============================================
void GProcessGtk_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessGtkO);
	m_GProcessGtkO = 0;
}
//===============================================
GProcessO* GProcessGtk() {
    if(m_GProcessGtkO == 0) {
        m_GProcessGtkO = GProcessGtk_New();
    }
    return m_GProcessGtkO;
}
//===============================================
static void GProcessGtk_Run(int argc, char** argv) {
    GConsole()->Print("[ ECHO ] GTK\n");
    gtk_init(&argc, &argv);
}
//===============================================
