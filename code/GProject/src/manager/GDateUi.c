//===============================================
#include "GDateUi.h"
#include "GProcess.h"
#include "GConfig.h"
#include "GManager.h"
#include "GDate.h"
//===============================================
#define B_ANSWER (256)
#define B_DATETIME (256)
//===============================================
static GDateUiO* m_GDateUiO = 0;
//===============================================
static void GDateUi_Run(int argc, char** argv);
//===============================================
static void GDateUi_Run_ADMIN(int argc, char** argv);
static void GDateUi_Run_INIT(int argc, char** argv);
static void GDateUi_Run_METHOD(int argc, char** argv);
static void GDateUi_Run_CHOICE(int argc, char** argv);
static void GDateUi_Run_SAVE(int argc, char** argv);
static void GDateUi_Run_LOAD(int argc, char** argv);
static void GDateUi_Run_QUIT(int argc, char** argv);
//===============================================
static void GDateUi_Run_DATE_SHOW(int argc, char** argv);
static void GDateUi_Run_TIME_SHOW(int argc, char** argv);
static void GDateUi_Run_DATE_TIME_SHOW(int argc, char** argv);
static void GDateUi_Run_DATE_LETTER_SHOW(int argc, char** argv);
//===============================================
GDateUiO* GDateUi_New() {
    GDateUiO* lObj = (GDateUiO*)malloc(sizeof(GDateUiO));
    lObj->Delete = GDateUi_Delete;
    lObj->Run = GDateUi_Run;
    return lObj;
}
//===============================================
void GDateUi_Delete() {
    GDateUiO* lObj = GDateUi();
    if(lObj != 0) {
        free(lObj);
    }
    m_GDateUiO = 0;
}
//===============================================
GDateUiO* GDateUi() {
    if(m_GDateUiO == 0) {
        m_GDateUiO = GDateUi_New();
    }
    return m_GDateUiO;
}
//===============================================
static void GDateUi_Run(int argc, char** argv) {
    m_GDateUiO->G_STATE = "S_INIT";
    while(1) {
        if(!strcmp(m_GDateUiO->G_STATE, "S_ADMIN")) {GDateUi_Run_ADMIN(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_INIT")) {GDateUi_Run_INIT(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_METHOD")) {GDateUi_Run_METHOD(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_CHOICE")) {GDateUi_Run_CHOICE(argc, argv);}
        //
        else if(!strcmp(m_GDateUiO->G_STATE, "S_DATE_SHOW")) {GDateUi_Run_DATE_SHOW(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_TIME_SHOW")) {GDateUi_Run_TIME_SHOW(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_DATE_TIME_SHOW")) {GDateUi_Run_DATE_TIME_SHOW(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_DATE_LETTER_SHOW")) {GDateUi_Run_DATE_LETTER_SHOW(argc, argv);}
        //
        else if(!strcmp(m_GDateUiO->G_STATE, "S_SAVE")) {GDateUi_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_LOAD")) {GDateUi_Run_LOAD(argc, argv);}
        else if(!strcmp(m_GDateUiO->G_STATE, "S_QUIT")) {GDateUi_Run_QUIT(argc, argv);}
        else break;
    }
}
//===============================================
static void GDateUi_Run_ADMIN(int argc, char** argv) {
    GProcess()->Run(argc, argv);
    m_GDateUiO->G_STATE = "S_END";
}
//===============================================
static void GDateUi_Run_INIT(int argc, char** argv) {
    printf("\n");
    printf("C_DATE !!!\n");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    printf("\t%-2s : %s\n", "-i", "reinitialiser l'application");
    printf("\t%-2s : %s\n", "-a", "redemarrer l'application");
    printf("\t%-2s : %s\n", "-v", "valider les configurations");
    printf("\n");
    m_GDateUiO->G_STATE = "S_LOAD";
}
//===============================================
static void GDateUi_Run_METHOD(int argc, char** argv) {
    printf("\n");
    printf("C_DATE :\n");
    printf("\t%-2s : %s\n", "1", "afficher la date");
    printf("\t%-2s : %s\n", "2", "afficher l'heure");
    printf("\t%-2s : %s\n", "3", "afficher la date et l'heure");
    printf("\t%-2s : %s\n", "4", "afficher la date LETTRE");
    printf("\n");
    m_GDateUiO->G_STATE = "S_CHOICE";
}
//===============================================
static void GDateUi_Run_CHOICE(int argc, char** argv) {
    char* lLast = GConfig()->GetData("G_DATE_ID");
    printf("C_DATE (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "")) {strcpy(lAnswer, lLast);}
    if(!strcmp(lAnswer, "-q")) {m_GDateUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GDateUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GDateUiO->G_STATE = "S_ADMIN";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GDateUiO->G_STATE = "S_DATE_SHOW"; GConfig()->SetData("G_DATE_ID", lAnswer);}
    else if(!strcmp(lAnswer, "2")) {m_GDateUiO->G_STATE = "S_TIME_SHOW"; GConfig()->SetData("G_DATE_ID", lAnswer);}
    else if(!strcmp(lAnswer, "3")) {m_GDateUiO->G_STATE = "S_DATE_TIME_SHOW"; GConfig()->SetData("G_DATE_ID", lAnswer);}
    else if(!strcmp(lAnswer, "4")) {m_GDateUiO->G_STATE = "S_DATE_LETTER_SHOW"; GConfig()->SetData("G_DATE_ID", lAnswer);}
    //
}
//===============================================
static void GDateUi_Run_DATE_SHOW(int argc, char** argv) {
    printf("\n");
    char lBuffer[B_DATETIME+1];
    GDate()->Date(lBuffer);
    printf("%-20s : %s\n", "Date", lBuffer);
    m_GDateUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GDateUi_Run_TIME_SHOW(int argc, char** argv) {
    printf("\n");
    char lBuffer[B_DATETIME+1];
    GDate()->Time(lBuffer);
    printf("%-20s : %s\n", "Date", lBuffer);
    m_GDateUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GDateUi_Run_DATE_TIME_SHOW(int argc, char** argv) {
    printf("\n");
    char lBuffer[B_DATETIME+1];
    GDate()->DateTime(lBuffer);
    printf("%-20s : %s\n", "Date", lBuffer);
    m_GDateUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GDateUi_Run_DATE_LETTER_SHOW(int argc, char** argv) {
    printf("\n");
    char lBuffer[B_DATETIME+1];
    GDate()->DateLetter(lBuffer);
    printf("%-20s : %s\n", "Date", lBuffer);
    m_GDateUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GDateUi_Run_SAVE(int argc, char** argv) {
    GConfig()->SaveData("G_DATE_ID");
    m_GDateUiO->G_STATE = "S_QUIT";
}
//===============================================
static void GDateUi_Run_LOAD(int argc, char** argv) {
    GConfig()->LoadData("G_DATE_ID");
    m_GDateUiO->G_STATE = "S_METHOD";
}
//===============================================
static void GDateUi_Run_QUIT(int argc, char** argv) {
    printf("\n");
    printf("C_QUIT (Oui/[N]on) ? ");
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "-q")) {m_GDateUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GDateUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GDateUiO->G_STATE = "S_ADMIN";}
    else if(!strcmp(lAnswer, "o")) {m_GDateUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "n")) {m_GDateUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "")) {m_GDateUiO->G_STATE = "S_INIT";}
}
//===============================================
