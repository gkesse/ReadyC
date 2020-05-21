//===============================================
#include "GProcess.h"
#include "GShell.h"
#include "GFile.h"
#include "GDir.h"
#include "GDebug.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Run(int argc, char** argv);
static void GProcess_Test(int argc, char** argv);
//===============================================
static void GProcess_Help(int argc, char** argv);
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));

    lObj->Delete = GProcess_Delete;
    lObj->Run = GProcess_Run;
    lObj->Test = GProcess_Test;
    return lObj;
}
//===============================================
void GProcess_Delete() {

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
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    int lRunFlag = 0;
    for(int i = 1; i < argc; i++) {
        char* lKey = argv[i];
        if(!strcmp(lKey, "test")) {GProcess_Test(argc, argv); lRunFlag = 1; break;}
    }
    if(lRunFlag == 0) {GProcess_Help(argc, argv);}
}
//===============================================
static void GProcess_Help(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    const char* lModule = "gp_c";
    printf("\n");
    printf("%s\n", "Description:");
    printf("\t%s\n", "Operations sur le module gp_c.");
    printf("\n");
    printf("%s\n", "Utilisation:");
    printf("\t\%s : %s\n", lModule, "afficher aide");
    printf("\t\%s %s : %s\n", lModule, "test", "lancer test");
    printf("\n");
}
//===============================================
static void GProcess_Test(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GFile()->Test(argc, argv);
}
//===============================================
