//===============================================
#include "GProcessConfig.h"
#include "GConfig.h"
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
void GProcessConfig_Delete(GProcessO* obj) {
    GProcess_Delete(obj);
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
    GConfig()->SetData("Nom", "KESSE");
    GConfig()->SetData("Prenom", "Gerard");
    GConfig()->SetData("Email", "gerard.kesse@readydev.com");
    GConfig()->SetData("Diplome", "Ingenieur");
    GConfig()->SetData("Formation", "Informatique Industrielle");
    GConfig()->SetData("Ecole", "Polytech'Montpellier");
    GConfig()->Show();
    GConfig()->Delete();
}
//===============================================
