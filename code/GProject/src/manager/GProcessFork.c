//===============================================
#include "GProcessFork.h"
//===============================================
static GProcessForkO* m_GProcessForkO = 0;
//===============================================
static void GProcessFork_Test(int argc, char** argv);
//===============================================
GProcessForkO* GProcessFork_New() {
    GProcessForkO* lObj = (GProcessForkO*)malloc(sizeof(GProcessForkO));
    lObj->Delete = GProcessFork_Delete;
    lObj->Test = GProcessFork_Test;
    return lObj;
}
//===============================================
void GProcessFork_Delete() {
    free(m_GProcessForkO);
    m_GProcessForkO = 0;
}
//===============================================
GProcessForkO* GProcessFork() {
    if(m_GProcessForkO == 0) {
        m_GProcessForkO = GProcessFork_New();
    }
    return m_GProcessForkO;
}
//===============================================
static void GProcessFork_Test(int argc, char** argv) {

}
//===============================================
