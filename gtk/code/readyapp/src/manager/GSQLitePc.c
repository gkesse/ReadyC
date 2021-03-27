//===============================================
#include "GSQLitePc.h"
#include "GSQLite.h"
#include "GManager.h"
//===============================================
static GSQLitePcO* m_GSQLitePcO = 0;
//===============================================
static void GSQLitePc_Run(int argc, char** argv);
static void GSQLitePc_RunShowVersion(int argc, char** argv);
static void GSQLitePc_RunTest(int argc, char** argv);
//===============================================
GSQLitePcO* GSQLitePc_New() {
    GSQLitePcO* lObj = (GSQLitePcO*)malloc(sizeof(GSQLitePcO));
    lObj->Delete = GSQLitePc_Delete;
    lObj->Run = GSQLitePc_Run;
    return lObj;
}
//===============================================
void GSQLitePc_Delete() {
    
}
//===============================================
GSQLitePcO* GSQLitePc() {
    if(m_GSQLitePcO == 0) {
        m_GSQLitePcO = GSQLitePc_New();
    }
    return m_GSQLitePcO;
}
//===============================================
static void GSQLitePc_Run(int argc, char** argv) {
    char* lKey = "test";
    if(argc > 2) {lKey = argv[2];}
    if(!strcmp(lKey, "show_version")) {GSQLitePc_RunShowVersion(argc, argv); return;}
    if(!strcmp(lKey, "test")) {GSQLitePc_RunTest(argc, argv); return;}
    GSQLitePc_RunShowVersion(argc, argv);
}
//===============================================
static void GSQLitePc_RunShowVersion(int argc, char** argv) {
    GSQLite()->ShowVersion();
}
//===============================================
static void GSQLitePc_RunTest(int argc, char** argv) {
    GSQLite()->QueryShow(GManager()->Format("\
    select type, name, tbl_name, rootpage\n\
    from sqlite_master\n\
    where type='table'\n\
    "), "10;15;15;10", 20);
}
//===============================================
