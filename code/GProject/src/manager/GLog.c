//===============================================
#include "GLog.h"
//===============================================
static GLogO* m_GLogO = 0;
//===============================================
static void GLog_Test(int argc, char** argv);
//===============================================
GLogO* GLog_New() {
    GLogO* lObj = (GLogO*)malloc(sizeof(GLogO));
    lObj->Delete = GLog_Delete;
    lObj->Test = GLog_Test;
    return lObj;
}
//===============================================
void GLog_Delete() {
    free(m_GLogO);
    m_GLogO = 0;
}
//===============================================
GLogO* GLog() {
    if(m_GLogO == 0) {
        m_GLogO = GLog_New();
    }
    return m_GLogO;
}
//===============================================
static void GLog_Test(int argc, char** argv) {

}
//===============================================
