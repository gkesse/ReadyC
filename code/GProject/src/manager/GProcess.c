//===============================================
#include "GProcess.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Process(int argc, char** argv);
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
    lObj->Delete = GProcess_Delete;
    lObj->Process = GProcess_Process;
    return lObj;
}
//===============================================
void GProcess_Delete() {
    GProcessO* lObj = GProcess();
    free(lObj);
    m_GProcessO = 0;
}
//===============================================
GProcessO* GProcess() {
    if(m_GProcessO == 0) {
        m_GProcessO = GProcess_New();
    }
    return m_GProcessO;
}
//===============================================
static void GProcess_Process(int argc, char** argv) {
	printf("%s()", __FUNCTION__);
}
//===============================================
