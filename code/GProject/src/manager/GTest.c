//===============================================
#include "GTest.h"
#include "GFile2.h"
#include "GString2.h"
#include "GConfig.h"
//===============================================
static GTestO* m_GTestO = 0;
//===============================================
static void GTest_Run(int argc, char** argv);
//===============================================
GTestO* GTest_New() {
    GTestO* lObj = (GTestO*)malloc(sizeof(GTestO));
    lObj->Delete = GTest_Delete;
    lObj->Run = GTest_Run;
    return lObj;
}
//===============================================
void GTest_Delete() {
    GTestO* lObj = GTest();
    free(lObj);
    m_GTestO = 0;
}
//===============================================
GTestO* GTest() {
    if(m_GTestO == 0) {
        m_GTestO = GTest_New();
    }
    return m_GTestO;
}
//===============================================
static void GTest_Run(int argc, char** argv) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
