//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GDebug.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Run(int argc, char** argv);
static void GProcess_Default(int argc, char** argv);
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
    lObj->Delete = GProcess_Delete;
    lObj->Run = GProcess_Run;
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
static void GProcess_Run(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    for(int i = 1; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "test")) {GTest()->Run(argc, argv); return;}
        break;
    }
    GProcess_Default(argc, argv);
}
//===============================================
static void GProcess_Default(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    printf("%s\n", __FUNCTION__);
}
//===============================================
