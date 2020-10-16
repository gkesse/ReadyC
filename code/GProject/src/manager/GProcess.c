//===============================================
#include "GProcess.h"
#include "GProcessUi.h"
#include "GManager.h"
//===============================================
#define B_ANSWER (256)
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Run(int argc, char** argv);
static void GProcess_Test(int argc, char** argv);
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
    lObj->Delete = GProcess_Delete;
    lObj->Test = GProcess_Test;
    lObj->Run = GProcess_Run;
    return lObj;
}
//===============================================
void GProcess_Delete() {
    GProcessO* lObj = GProcess();
    if(lObj != 0) {
        free(lObj);
    }
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
    char* lKey = "ui";
    if(argc >= 2) lKey = argv[1];
    if(!strcmp(lKey, "ui")) {GProcessUi()->Run(argc, argv); return;}
    if(!strcmp(lKey, "test")) {GProcess()->Test(argc, argv); return;}
    GProcessUi()->Run(argc, argv);
}
//===============================================
static void GProcess_Test(int argc, char** argv) {
    GManager()->Test(argc, argv);
}
//===============================================
