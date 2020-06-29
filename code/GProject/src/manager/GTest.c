//===============================================
#include "GTest.h"
#include "GTestBasic.h"
//===============================================
static GTestO* m_GTestO = 0;
//===============================================
static void GTest_Run(int argc, char** argv);
static void GTest_Default(int argc, char** argv);
static void GTest_String(int argc, char** argv);
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
    for(int i = 2; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "basic")) {GTestBasic()->Run(argc, argv); return;}
        if(!strcmp(lKey, "alarm")) {GTest_String(argc, argv); return;}
        break;
    }
    GTest_Default(argc, argv);
}
//===============================================
static void GTest_Default(int argc, char** argv) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
static void GTest_String(int argc, char** argv) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
