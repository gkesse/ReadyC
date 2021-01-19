//===============================================
#include "GProcessUi.h"
#include "GSQLiteUi.h"
#include "GOpenCVUi.h"
#include "GConfig.h"
#include "GManager.h"
//===============================================
#define B_ANSWER (256)
//===============================================
static GProcessUiO* m_GProcessUiO = 0;
//===============================================
static void GProcessUi_Run(int argc, char** argv);
//===============================================
static void GProcessUi_Run_INIT(int argc, char** argv);
static void GProcessUi_Run_METHOD(int argc, char** argv);
static void GProcessUi_Run_CHOICE(int argc, char** argv);
static void GProcessUi_Run_SAVE(int argc, char** argv);
static void GProcessUi_Run_LOAD(int argc, char** argv);
//===============================================
static void GProcessUi_Run_SQLITE(int argc, char** argv);
static void GProcessUi_Run_OPENCV(int argc, char** argv);
//===============================================
GProcessUiO* GProcessUi_New() {
    GProcessUiO* lObj = (GProcessUiO*)malloc(sizeof(GProcessUiO));
    lObj->Delete = GProcessUi_Delete;
    lObj->Run = GProcessUi_Run;
    return lObj;
}
//===============================================
void GProcessUi_Delete() {

}
//===============================================
GProcessUiO* GProcessUi() {
    if(m_GProcessUiO == 0) {
        m_GProcessUiO = GProcessUi_New();
    }
    return m_GProcessUiO;
}
//===============================================
static void GProcessUi_Run(int argc, char** argv) {
    m_GProcessUiO->G_STATE = "S_INIT";
    while(1) {
        if(!strcmp(m_GProcessUiO->G_STATE, "S_INIT")) {GProcessUi_Run_INIT(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_METHOD")) {GProcessUi_Run_METHOD(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_CHOICE")) {GProcessUi_Run_CHOICE(argc, argv);}
        //
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_SQLITE")) {GProcessUi_Run_SQLITE(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_OPENCV")) {GProcessUi_Run_OPENCV(argc, argv);}
        //
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_SAVE")) {GProcessUi_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_LOAD")) {GProcessUi_Run_LOAD(argc, argv);}
        else break;
    }
}
//===============================================
static void GProcessUi_Run_INIT(int argc, char** argv) {
    printf("\n");
    printf("C_ADMIN !!!\n");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    m_GProcessUiO->G_STATE = "S_LOAD";
}
//===============================================
static void GProcessUi_Run_METHOD(int argc, char** argv) {
    printf("\n");
    printf("C_ADMIN :\n");
    printf("\t%-2s : %s\n", "1", "S_SQLITE");
    printf("\t%-2s : %s\n", "2", "S_OPENCV");
    printf("\n");
    m_GProcessUiO->G_STATE = "S_CHOICE";
}
//===============================================
static void GProcessUi_Run_CHOICE(int argc, char** argv) {
    char* lLast = GConfig()->GetData("G_ADMIN_ID");
    printf("C_ADMIN (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "")) {strcpy(lAnswer, lLast);}
    if(!strcmp(lAnswer, "-q")) {m_GProcessUiO->G_STATE = "S_END";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GProcessUiO->G_STATE = "S_SQLITE"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "2")) {m_GProcessUiO->G_STATE = "S_OPENCV"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
}
//===============================================
static void GProcessUi_Run_SQLITE(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_OPENCV(int argc, char** argv) {
    GOpenCVUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_SAVE(int argc, char** argv) {
    GConfig()->SaveData("G_ADMIN_ID");
    m_GProcessUiO->G_STATE = "S_END";
}
//===============================================
static void GProcessUi_Run_LOAD(int argc, char** argv) {
    GConfig()->LoadData("G_ADMIN_ID");
    m_GProcessUiO->G_STATE = "S_METHOD";
}
//===============================================
