//===============================================
#include "GSQLiteUi.h"
#include "GProcess.h"
#include "GSQLite.h"
#include "GConfig.h"
#include "GManager.h"
//===============================================
#define B_ANSWER (256)
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
static void GSQLiteUi_Run_CONFIG_DATA_CREATE(int argc, char** argv);
static void GSQLiteUi_Run_CONFIG_DATA_DROP(int argc, char** argv);
static void GSQLiteUi_Run_CONFIG_DATA_SHOW(int argc, char** argv);
//===============================================
GSQLiteUiO* GSQLiteUi_New() {
    GSQLiteUiO* lObj = (GSQLiteUiO*)malloc(sizeof(GSQLiteUiO));
    lObj->Delete = GSQLiteUi_Delete;
    lObj->Run = GSQLiteUi_Run;
    return lObj;
}
//===============================================
void GSQLiteUi_Delete() {

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
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_CONFIG_DATA_CREATE")) {GSQLiteUi_Run_CONFIG_DATA_CREATE(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_CONFIG_DATA_DROP")) {GSQLiteUi_Run_CONFIG_DATA_DROP(argc, argv);}
        else if(!strcmp(m_GSQLiteUiO->G_STATE, "S_CONFIG_DATA_SHOW")) {GSQLiteUi_Run_CONFIG_DATA_SHOW(argc, argv);}
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
    m_GSQLiteUiO->G_STATE = "S_LOAD";
}
//===============================================
static void GSQLiteUi_Run_METHOD(int argc, char** argv) {
    printf("\n");
    printf("C_SQLITE :\n");
    printf("\t%-2s : %s\n", "1", "afficher les tables");
    printf("\t%-2s : %s\n", "2", "creer la table config_data");
    printf("\t%-2s : %s\n", "3", "supprimer la table config_data");
    printf("\t%-2s : %s\n", "4", "afficher les donnees de la table config_data");
    printf("\n");
    m_GSQLiteUiO->G_STATE = "S_CHOICE";
}
//===============================================
static void GSQLiteUi_Run_CHOICE(int argc, char** argv) {
    char* lLast = GConfig()->GetData("G_SQLITE_ID");
    printf("C_SQLITE (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "")) {strcpy(lAnswer, lLast);}
    if(!strcmp(lAnswer, "-q")) {m_GSQLiteUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GSQLiteUiO->G_STATE = "S_ADMIN";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GSQLiteUiO->G_STATE = "S_TABLES_SHOW"; GConfig()->SetData("G_SQLITE_ID", lAnswer);}
    else if(!strcmp(lAnswer, "2")) {m_GSQLiteUiO->G_STATE = "S_CONFIG_DATA_CREATE"; GConfig()->SetData("G_SQLITE_ID", lAnswer);}
    else if(!strcmp(lAnswer, "3")) {m_GSQLiteUiO->G_STATE = "S_CONFIG_DATA_DROP"; GConfig()->SetData("G_SQLITE_ID", lAnswer);}
    else if(!strcmp(lAnswer, "4")) {m_GSQLiteUiO->G_STATE = "S_CONFIG_DATA_SHOW"; GConfig()->SetData("G_SQLITE_ID", lAnswer);}
    //
}
//===============================================
static void GSQLiteUi_Run_TABLES_SHOW(int argc, char** argv) {
    printf("\n");
    
    GSQLite()->QueryShow(GManager()->Format("\
    select name from sqlite_master\n\
    where type='table'\n\
    "), "20;30", 20);
    
    m_GSQLiteUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GSQLiteUi_Run_CONFIG_DATA_CREATE(int argc, char** argv) {
    printf("\n");

    GSQLite()->QueryWrite(GManager()->Format("\
    create table if not exists config_data (\n\
    config_key text,\n\
    config_value text\n\
    )"));
    
    m_GSQLiteUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GSQLiteUi_Run_CONFIG_DATA_DROP(int argc, char** argv) {
    printf("\n");
    
    GSQLite()->QueryWrite(GManager()->Format("\
    drop table if exists config_data\n\
    "));

    m_GSQLiteUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GSQLiteUi_Run_CONFIG_DATA_SHOW(int argc, char** argv) {
    printf("\n");

    GSQLite()->QueryShow(GManager()->Format("\
    select * from config_data\n\
    "), "20;30", 25);
    
    m_GSQLiteUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GSQLiteUi_Run_SAVE(int argc, char** argv) {
    GConfig()->SaveData("G_SQLITE_ID");
    m_GSQLiteUiO->G_STATE = "S_QUIT";
}
//===============================================
static void GSQLiteUi_Run_LOAD(int argc, char** argv) {
    GConfig()->LoadData("G_SQLITE_ID");
    m_GSQLiteUiO->G_STATE = "S_METHOD";
}
//===============================================
static void GSQLiteUi_Run_QUIT(int argc, char** argv) {
    printf("\n");
    printf("C_QUIT (Oui/[N]on) ? ");
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "-q")) {m_GSQLiteUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "-i")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "-a")) {m_GSQLiteUiO->G_STATE = "S_ADMIN";}
    else if(!strcmp(lAnswer, "o")) {m_GSQLiteUiO->G_STATE = "S_END";}
    else if(!strcmp(lAnswer, "n")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
    else if(!strcmp(lAnswer, "")) {m_GSQLiteUiO->G_STATE = "S_INIT";}
}
//===============================================
