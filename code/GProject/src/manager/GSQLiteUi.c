//===============================================
#include "GSQLiteUi.h"
#include "GProcess.h"
#include "GMap.h"
//===============================================
#define B_ANSWER (256)
//===============================================
GDECLARE_MAP(GSQLiteUi, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GSQLiteUi, GCHAR_PTR, GVOID_PTR)
//===============================================
static GSQLiteUiO* m_GSQLiteUiO = 0;
//===============================================
static void GSQLiteUi_Run(int argc, char** argv);
//===============================================
static void GSQLiteUi_Run_ADMIN(int argc, char** argv);
static void GSQLiteUi_Run_INIT(int argc, char** argv);
static void GSQLiteUi_Run_METHOD(int argc, char** argv);
static void GSQLiteUi_Run_CHOICE(int argc, char** argv);
static void GSQLiteUi_Run_SAVE(int argc, char** argv);
static void GSQLiteUi_Run_LOAD(int argc, char** argv);
static void GSQLiteUi_Run_QUIT(int argc, char** argv);
//===============================================
static void GSQLiteUi_Run_SQLITE(int argc, char** argv);
//===============================================
GSQLiteUiO* GSQLiteUi_New() {
    GSQLiteUiO* lObj = (GSQLiteUiO*)malloc(sizeof(GSQLiteUiO));
    lObj->Delete = GSQLiteUi_Delete;
    lObj->Run = GSQLiteUi_Run;
    return lObj;
}
//===============================================
void GSQLiteUi_Delete() {
    GSQLiteUiO* lObj = GSQLiteUi();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSQLiteUiO = 0;
}
//===============================================
GSQLiteUiO* GSQLiteUi() {
    if(m_GSQLiteUiO == 0) {
        m_GSQLiteUiO = GSQLiteUi_New();
    }
    return m_GSQLiteUiO;
}
//===============================================
static void GSQLiteUi_Run(int argc, char** argv) {
    m_GSQLiteUiO->G_STATE = "S_INIT";
    while(1) {
        if(!strcmp(m_GSQLiteUiO->G_STATE, "S_ADMIN")) {GSQLiteUi_Run_ADMIN(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_INIT")) {GSQLiteUi_Run_INIT(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_METHOD")) {GSQLiteUi_Run_METHOD(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_CHOICE")) {GSQLiteUi_Run_CHOICE(argc, argv);}
        //
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_SQLITE")) {GSQLiteUi_Run_SQLITE(argc, argv);}
        //
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_SAVE")) {GSQLiteUi_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_LOAD")) {GSQLiteUi_Run_LOAD(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_QUIT")) {GSQLiteUi_Run_QUIT(argc, argv);}
        else break;
    }
}
//===============================================
static void GSQLiteUi_Run_ADMIN(int argc, char** argv) {
    GProcess()->run(argc, argv);
    m_GSQLiteUiO->G_STATE = "S_END";
}
//===============================================
static void GSQLiteUi_Run_INIT(int argc, char** argv) {
    printf("\n");
    printf("C_SQLITE !!!\n");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    printf("\t%-2s : %s\n", "-i", "reinitialiser l'application");
    printf("\t%-2s : %s\n", "-a", "redemarrer l'application");
    printf("\t%-2s : %s\n", "-v", "valider les configurations");
    printf("\n");
    m_GSQLiteUiO->G_STATE = "S_LOAD";
}
//===============================================
static void GSQLiteUi_Run_METHOD(int argc, char** argv) {
    printf("C_SQLITE :\n");
    printf("\t%-2s : %s\n", "1", "afficher les tables");
    printf("\t%-2s : %s\n", "2", "extraire le schema d'une table");
    printf("\n");
    printf("\t%-2s : %s\n", "10", "creer la table CONFIG_C");
    printf("\t%-2s : %s\n", "11", "supprimer la table CONFIG_C");
    printf("\t%-2s : %s\n", "12", "afficher les donnees de la table CONFIG_C");
    printf("\t%-2s : %s\n", "13", "supprimer une donnees de la table CONFIG_C");
    printf("\n");
    m_GSQLiteUiO->G_STATE = "S_CHOICE";
}
//===============================================
static void GSQLiteUi_Run_CHOICE(int argc, char** argv) {
    char* lLast = "";
    printf("C_SQLITE (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; fgets(lAnswer, B_ANSWER, stdin); lAnswer[strlen(lAnswer)-1] = 0;
    if(!strcmp(lAnswer, "-q")) {m_GSQLiteUiO->G_STATE = "S_END";}
    if(!strcmp(lAnswer, "-i")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
    if(!strcmp(lAnswer, "-a")) {m_GSQLiteUiO->G_STATE = "S_ADMIN";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GSQLiteUiO->G_STATE = "S_SQLITE";}
    else if(!strcmp(lAnswer, "2")) {m_GSQLiteUiO->G_STATE = "S_SQLITE";}
    //
    else if(!strcmp(lAnswer, "10")) {m_GSQLiteUiO->G_STATE = "S_SQLITE";}
    else if(!strcmp(lAnswer, "11")) {m_GSQLiteUiO->G_STATE = "S_SQLITE";}
    else if(!strcmp(lAnswer, "12")) {m_GSQLiteUiO->G_STATE = "S_SQLITE";}
    else if(!strcmp(lAnswer, "13")) {m_GSQLiteUiO->G_STATE = "S_SQLITE";}
    //
}
//===============================================
static void GSQLiteUi_Run_SQLITE(int argc, char** argv) {
    printf("\n");
    printf("run_SQLITE\n");
    m_GSQLiteUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GSQLiteUi_Run_SAVE(int argc, char** argv) {
    m_GSQLiteUiO->G_STATE = "S_QUIT";
}
//===============================================
static void GSQLiteUi_Run_LOAD(int argc, char** argv) {
    m_GSQLiteUiO->G_STATE = "S_METHOD";
}
//===============================================
static void GSQLiteUi_Run_QUIT(int argc, char** argv) {
    printf("\n");
    m_GSQLiteUiO->G_STATE = "S_END";
}
//===============================================
