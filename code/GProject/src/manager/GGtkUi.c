//===============================================
#include "GGtkUi.h"
#include "GProcess.h"
#include "GConfig.h"
#include "GManager.h"
#include "GGtk.h"
//===============================================
#define B_ANSWER (256)
#define B_DATETIME (256)
//===============================================
static GGtkUiO* m_GGtkUiO = 0;
//===============================================
static void GGtkUi_Run(int argc, char** argv);
//===============================================
static void GGtkUi_Run_ADMIN(int argc, char** argv);
static void GGtkUi_Run_INIT(int argc, char** argv);
static void GGtkUi_Run_METHOD(int argc, char** argv);
static void GGtkUi_Run_CHOICE(int argc, char** argv);
static void GGtkUi_Run_SAVE(int argc, char** argv);
static void GGtkUi_Run_LOAD(int argc, char** argv);
static void GGtkUi_Run_QUIT(int argc, char** argv);
//===============================================
static void GGtkUi_Run_TEST(int argc, char** argv);
//===============================================
GGtkUiO* GGtkUi_New() {
    GGtkUiO* lObj = (GGtkUiO*)malloc(sizeof(GGtkUiO));
    lObj->Delete = GGtkUi_Delete;
    lObj->Run = GGtkUi_Run;
    return lObj;
}
//===============================================
void GGtkUi_Delete() {
    GGtkUiO* lObj = GGtkUi();
    if(lObj != 0) {
        free(lObj);
    }
    m_GGtkUiO = 0;
}
//===============================================
GGtkUiO* GGtkUi() {
    if(m_GGtkUiO == 0) {
        m_GGtkUiO = GGtkUi_New();
    }
    return m_GGtkUiO;
}
//===============================================
static void GGtkUi_Run(int argc, char** argv) {
    m_GGtkUiO->G_STATE = "S_INIT";
    while(1) {
        if(!strcmp(m_GGtkUiO->G_STATE, "S_ADMIN")) {GGtkUi_Run_ADMIN(argc, argv);}
        else if(!strcmp(m_GGtkUiO->G_STATE, "S_INIT")) {GGtkUi_Run_INIT(argc, argv);}
        else if(!strcmp(m_GGtkUiO->G_STATE, "S_METHOD")) {GGtkUi_Run_METHOD(argc, argv);}
        else if(!strcmp(m_GGtkUiO->G_STATE, "S_CHOICE")) {GGtkUi_Run_CHOICE(argc, argv);}
        //
        else if(!strcmp(m_GGtkUiO->G_STATE, "S_TEST")) {GGtkUi_Run_TEST(argc, argv);}
        //
        else if(!strcmp(m_GGtkUiO->G_STATE, "S_SAVE")) {GGtkUi_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GGtkUiO->G_STATE, "S_LOAD")) {GGtkUi_Run_LOAD(argc, argv);}
        else if(!strcmp(m_GGtkUiO->G_STATE, "S_QUIT")) {GGtkUi_Run_QUIT(argc, argv);}
        else break;
    }
}
//===============================================
static void GGtkUi_Run_ADMIN(int argc, char** argv) {
    GProcess()->Run(argc, argv);
    m_GGtkUiO->G_STATE = "S_END";
}
//===============================================
static void GGtkUi_Run_INIT(int argc, char** argv) {
    printf("\n");
    printf("C_DATE !!!\n");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    printf("\t%-2s : %s\n", "-i", "reinitialiser l'application");
    printf("\t%-2s : %s\n", "-a", "redemarrer l'application");
    printf("\t%-2s : %s\n", "-v", "valider les configurations");
    printf("\n");
    m_GGtkUiO->G_STATE = "S_LOAD";
}
//===============================================
static void GGtkUi_Run_METHOD(int argc, char** argv) {
    printf("\n");
    printf("C_DATE :\n");
    printf("\t%-2s : %s\n", "1", "lancer un test");
    printf("\n");
    m_GGtkUiO->G_STATE = "S_CHOICE";
}
//===============================================
static void GGtkUi_Run_CHOICE(int argc, char** argv) {
    char* lLast = GConfig()->GetData("G_DATE_ID");
    printf("C_DATE (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "")) {strcpy(lAnswer, lLast);}
    if(!strcmp(lAnswer, "-q")) {m_GGtkUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GGtkUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GGtkUiO->G_STATE = "S_ADMIN";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GGtkUiO->G_STATE = "S_TEST"; GConfig()->SetData("G_DATE_ID", lAnswer);}
    //
}
//===============================================
static void GGtkUi_Run_TEST(int argc, char** argv) {
    printf("\n");
    printf("lancement du test GTK...\n");
    m_GGtkUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GGtkUi_Run_SAVE(int argc, char** argv) {
    GConfig()->SaveData("G_DATE_ID");
    m_GGtkUiO->G_STATE = "S_QUIT";
}
//===============================================
static void GGtkUi_Run_LOAD(int argc, char** argv) {
    GConfig()->LoadData("G_DATE_ID");
    m_GGtkUiO->G_STATE = "S_METHOD";
}
//===============================================
static void GGtkUi_Run_QUIT(int argc, char** argv) {
    printf("\n");
    printf("C_QUIT (Oui/[N]on) ? ");
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "-q")) {m_GGtkUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GGtkUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GGtkUiO->G_STATE = "S_ADMIN";}
    else if(!strcmp(lAnswer, "o")) {m_GGtkUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "n")) {m_GGtkUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "")) {m_GGtkUiO->G_STATE = "S_INIT";}
}
//===============================================
