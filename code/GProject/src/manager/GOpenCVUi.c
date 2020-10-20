//===============================================
#include "GOpenCVUi.h"
#include "GProcess.h"
#include "GConfig.h"
#include "GManager.h"
#include "GOpenCV.h"
//===============================================
#if defined(_GUSE_OPENCV_ON_)
//===============================================
#define B_ANSWER (256)
#define B_OPENCVTIME (256)
//===============================================
static GOpenCVUiO* m_GOpenCVUiO = 0;
//===============================================
static void GOpenCVUi_Run(int argc, char** argv);
//===============================================
static void GOpenCVUi_Run_ADMIN(int argc, char** argv);
static void GOpenCVUi_Run_INIT(int argc, char** argv);
static void GOpenCVUi_Run_METHOD(int argc, char** argv);
static void GOpenCVUi_Run_CHOICE(int argc, char** argv);
static void GOpenCVUi_Run_SAVE(int argc, char** argv);
static void GOpenCVUi_Run_LOAD(int argc, char** argv);
static void GOpenCVUi_Run_QUIT(int argc, char** argv);
//===============================================
static void GOpenCVUi_Run_OPEN(int argc, char** argv);
static void GOpenCVUi_Run_CLOSE(int argc, char** argv);
//===============================================
GOpenCVUiO* GOpenCVUi_New() {
    GOpenCVUiO* lObj = (GOpenCVUiO*)malloc(sizeof(GOpenCVUiO));
    lObj->Delete = GOpenCVUi_Delete;
    lObj->Run = GOpenCVUi_Run;
    return lObj;
}
//===============================================
void GOpenCVUi_Delete() {
    GOpenCVUiO* lObj = GOpenCVUi();
    if(lObj != 0) {
        free(lObj);
    }
    m_GOpenCVUiO = 0;
}
//===============================================
GOpenCVUiO* GOpenCVUi() {
    if(m_GOpenCVUiO == 0) {
        m_GOpenCVUiO = GOpenCVUi_New();
    }
    return m_GOpenCVUiO;
}
//===============================================
static void GOpenCVUi_Run(int argc, char** argv) {
    m_GOpenCVUiO->G_STATE = "S_INIT";
    while(1) {
        if(!strcmp(m_GOpenCVUiO->G_STATE, "S_ADMIN")) {GOpenCVUi_Run_ADMIN(argc, argv);}
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_INIT")) {GOpenCVUi_Run_INIT(argc, argv);}
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_METHOD")) {GOpenCVUi_Run_METHOD(argc, argv);}
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_CHOICE")) {GOpenCVUi_Run_CHOICE(argc, argv);}
        //
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_OPEN")) {GOpenCVUi_Run_OPEN(argc, argv);}
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_CLOSE")) {GOpenCVUi_Run_CLOSE(argc, argv);}
        //
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_SAVE")) {GOpenCVUi_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_LOAD")) {GOpenCVUi_Run_LOAD(argc, argv);}
        else if(!strcmp(m_GOpenCVUiO->G_STATE, "S_QUIT")) {GOpenCVUi_Run_QUIT(argc, argv);}
        else break;
    }
}
//===============================================
static void GOpenCVUi_Run_ADMIN(int argc, char** argv) {
    GProcess()->Run(argc, argv);
    m_GOpenCVUiO->G_STATE = "S_END";
}
//===============================================
static void GOpenCVUi_Run_INIT(int argc, char** argv) {
    printf("\n");
    printf("C_OPENCV !!!\n");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    printf("\t%-2s : %s\n", "-i", "reinitialiser l'application");
    printf("\t%-2s : %s\n", "-a", "redemarrer l'application");
    printf("\t%-2s : %s\n", "-v", "valider les configurations");
    printf("\n");
    m_GOpenCVUiO->G_STATE = "S_LOAD";
}
//===============================================
static void GOpenCVUi_Run_METHOD(int argc, char** argv) {
    printf("\n");
    printf("C_OPENCV :\n");
    printf("\t%-2s : %s\n", "1", "ouvrir l'application");
    printf("\t%-2s : %s\n", "2", "fermer l'application");
    printf("\n");
    m_GOpenCVUiO->G_STATE = "S_CHOICE";
}
//===============================================
static void GOpenCVUi_Run_CHOICE(int argc, char** argv) {
    char* lLast = GConfig()->GetData("G_OPENCV_ID");
    printf("C_OPENCV (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "")) {strcpy(lAnswer, lLast);}
    if(!strcmp(lAnswer, "-q")) {m_GOpenCVUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GOpenCVUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GOpenCVUiO->G_STATE = "S_ADMIN";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GOpenCVUiO->G_STATE = "S_OPEN"; GConfig()->SetData("G_OPENCV_ID", lAnswer);}
    else if(!strcmp(lAnswer, "2")) {m_GOpenCVUiO->G_STATE = "S_CLOSE"; GConfig()->SetData("G_OPENCV_ID", lAnswer);}
    //
}
//===============================================
static void GOpenCVUi_Run_OPEN(int argc, char** argv) {
    GManager()->Trace(3, "[info] ouverture de l'application : ok", 0);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GOpenCVUi_Run_CLOSE(int argc, char** argv) {
    GManager()->Trace(3, "[info] fermeture de l'application : ok", 0);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GOpenCVUi_Run_SAVE(int argc, char** argv) {
    GConfig()->SaveData("G_OPENCV_ID");
    m_GOpenCVUiO->G_STATE = "S_QUIT";
}
//===============================================
static void GOpenCVUi_Run_LOAD(int argc, char** argv) {
    GConfig()->LoadData("G_OPENCV_ID");
    m_GOpenCVUiO->G_STATE = "S_METHOD";
}
//===============================================
static void GOpenCVUi_Run_QUIT(int argc, char** argv) {
    printf("\n");
    printf("C_QUIT (Oui/[N]on) ? ");
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "-q")) {m_GOpenCVUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GOpenCVUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GOpenCVUiO->G_STATE = "S_ADMIN";}
    else if(!strcmp(lAnswer, "o")) {m_GOpenCVUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "n")) {m_GOpenCVUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "")) {m_GOpenCVUiO->G_STATE = "S_INIT";}
}
//===============================================
#endif
//===============================================
