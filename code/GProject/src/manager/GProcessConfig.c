//===============================================
#include "GProcessConfig.h"
#include "GConfig.h"
#include "GLog.h"
//===============================================
static GProcessO* m_GProcessConfigO = 0;
//===============================================
static void GProcessConfig_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessConfig_New() {
    GProcessO* lParent = GProcess_New();
    GProcessConfigO* lChild = (GProcessConfigO*)malloc(sizeof(GProcessConfigO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessConfig_Delete;
    lParent->Run = GProcessConfig_Run;
    return lParent;
}
//===============================================
void GProcessConfig_Delete() {
	GProcess_Delete(m_GProcessConfigO);
	m_GProcessConfigO = 0;
}
//===============================================
GProcessO* GProcessConfig() {
    if(m_GProcessConfigO == 0) {
        m_GProcessConfigO = GProcessConfig_New();
    }
    return m_GProcessConfigO;
}
//===============================================
static void GProcessConfig_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessConfig_Run");
    //GLog()->Write("#================================================");
    GConfig()->SetData("Nom", "KESSE");
    GConfig()->SetData("Prenom", "Gerard");
    GConfig()->SetData("Email", "gerard.kesse@readydev.com");
    GConfig()->SetData("Diplome", "Ingenieur");
    GConfig()->SetData("Formation", "Informatique Industrielle");
    GConfig()->SetData("Ecole", "Polytech'Montpellier");
    GConfig()->Show();
}
//===============================================
