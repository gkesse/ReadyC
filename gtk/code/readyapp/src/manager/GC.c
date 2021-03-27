//===============================================
#include "GC.h"
//===============================================
static GCO* m_GCO = 0;
//===============================================
static void GC_Test(int argc, char** argv);
//===============================================
GCO* GC_New() {
    GCO* lObj = (GCO*)malloc(sizeof(GCO));
    lObj->Delete = GC_Delete;
    lObj->Test = GC_Test;
    return lObj;
}
//===============================================
void GC_Delete() {

}
//===============================================
GCO* GC() {
    if(m_GCO == 0) {
        m_GCO = GC_New();
    }
    return m_GCO;
}
//===============================================
static void GC_Test(int argc, char** argv) {
    printf("Bonjour tout le monde\n");
}
//===============================================
