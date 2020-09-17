//===============================================
#include "GGtk.h"
#include "GManager.h"
//===============================================
static GGtkO* m_GGtkO = 0;
//===============================================
static void GGtk_Test(int argc, char** argv);
//===============================================
GGtkO* GGtk_New() {
	GGtkO* lObj = (GGtkO*)malloc(sizeof(GGtkO));

	lObj->Delete = GGtk_Delete;
	lObj->Test = GGtk_Test;
	return lObj;
}
//===============================================
void GGtk_Delete() {
    GGtkO* lObj = GGtk();
    if(lObj != 0) {
        free(lObj);
    }
    m_GGtkO = 0;
}
//===============================================
GGtkO* GGtk() {
	if(m_GGtkO == 0) {
		m_GGtkO = GGtk_New();
	}
	return m_GGtkO;
}
//===============================================
static void GGtk_Test(int argc, char** argv) {
    printf("lancement du test du programme\n");
}
//===============================================
