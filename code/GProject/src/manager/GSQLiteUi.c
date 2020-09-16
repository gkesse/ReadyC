//===============================================
#include "GSQLiteUi.h"
#include "GProcess.h"
#include "GSQLiteMgr.h"
//===============================================
#define B_ANSWER (256)
#define B_QUERY (256)
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
static void GSQLiteUi_Run_TABLES_SHOW(int argc, char** argv);
static void GSQLiteUi_Run_CONIG_CREATE(int argc, char** argv);
static void GSQLiteUi_Run_CONIG_DELETE(int argc, char** argv);
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
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_TABLES_SHOW")) {GSQLiteUi_Run_TABLES_SHOW(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_CONIG_CREATE")) {GSQLiteUi_Run_CONIG_CREATE(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_CONIG_DELETE")) {GSQLiteUi_Run_CONIG_DELETE(argc, argv);}
        //
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_SAVE")) {GSQLiteUi_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_LOAD")) {GSQLiteUi_Run_LOAD(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_QUIT")) {GSQLiteUi_Run_QUIT(argc, argv);}
        else break;
    }
}
//===============================================
static void GSQLiteUi_Run_ADMIN(int argc, char** argv) {
    GProcess()->Run(argc, argv);
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
    else if(!strcmp(lAnswer, "1")) {m_GSQLiteUiO->G_STATE = "S_TABLES_SHOW";}
    else if(!strcmp(lAnswer, "2")) {m_GSQLiteUiO->G_STATE = "S_TABLES_SHOW";}
    //
    else if(!strcmp(lAnswer, "10")) {m_GSQLiteUiO->G_STATE = "S_CONIG_CREATE";}
    else if(!strcmp(lAnswer, "11")) {m_GSQLiteUiO->G_STATE = "S_CONIG_DELETE";}
    else if(!strcmp(lAnswer, "12")) {m_GSQLiteUiO->G_STATE = "S_TABLES_SHOW";}
    else if(!strcmp(lAnswer, "13")) {m_GSQLiteUiO->G_STATE = "S_TABLES_SHOW";}
    //
}
//===============================================
static void GSQLiteUi_Run_TABLES_SHOW(int argc, char** argv) {
    printf("\n");
    char lSqlQuery[B_QUERY+1];

    sprintf(lSqlQuery, "\
    select * from CONFIG_C \
    limit 100 \
    ");
    
    GSQLiteMgr()->QueryShow(lSqlQuery, "20;30", 25);
    
    m_GSQLiteUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GSQLiteUi_Run_CONIG_CREATE(int argc, char** argv) {
    printf("\n");
    char lSqlQuery[B_QUERY+1];

    sprintf(lSqlQuery, "\
    create table CONFIG_C ( \
    CONFIG_KEY text unique not null, \
    CONFIG_VALUE text \
    )");
    
    GSQLiteMgr()->QueryWrite(lSqlQuery);
    m_GSQLiteUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GSQLiteUi_Run_CONIG_DELETE(int argc, char** argv) {
    printf("\n");
    char lSqlQuery[B_QUERY+1];

    sprintf(lSqlQuery, "\
    drop table CONFIG_C ( \
    )");
    
    GSQLiteMgr()->QueryWrite(lSqlQuery);
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
    printf("C_QUIT (Oui/[N]on) ? ");
    char lAnswer[B_ANSWER+1]; fgets(lAnswer, B_ANSWER, stdin); lAnswer[strlen(lAnswer)-1] = 0;
    if(!strcmp(lAnswer, "-q")) {m_GSQLiteUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GSQLiteUiO->G_STATE = "S_ADMIN";}
    else if(!strcmp(lAnswer, "o")) {m_GSQLiteUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "n")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
}
//===============================================
