//===============================================
#include "GProcess.h"
#include "GProcessUi.h"
#include "GGtk.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Run(int argc, char** argv);
static void GProcess_RunTest(int argc, char** argv);
static void GProcess_RunUi(int argc, char** argv);
static void GProcess_RunGtk(int argc, char** argv);
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
    lObj->Delete = GProcess_Delete;
    lObj->Run = GProcess_Run;
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
    char* lKey = "test";
    if(argc > 1) {lKey = argv[1];}
    if(!strcmp(lKey, "test")) {GProcess_RunTest(argc, argv); return;}
    if(!strcmp(lKey, "ui")) {GProcess_RunUi(argc, argv); return;}
    if(!strcmp(lKey, "gtk")) {GProcess_RunGtk(argc, argv); return;}
    GProcess_RunTest(argc, argv);
}
//===============================================
static void GProcess_RunTest(int argc, char** argv) {
    printf("GProcess_RunTest\n");
}
//===============================================
static void GProcess_RunUi(int argc, char** argv) {
    GProcessUi()->Run(argc, argv);
}
//===============================================
static void GProcess_RunGtk(int argc, char** argv) {
    GGtk()->Run(argc, argv);
}
//===============================================
