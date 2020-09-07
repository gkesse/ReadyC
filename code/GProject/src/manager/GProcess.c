//===============================================
#include "GProcess.h"
#include "GMap.h"
//===============================================
#define B_ANSWER (256)
//===============================================
GDECLARE_MAP(GProcess, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GProcess, GCHAR_PTR, GVOID_PTR)
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Run(int argc, char** argv);
//===============================================
static void GProcess_Run_ADMIN(int argc, char** argv);
static void GProcess_Run_INIT(int argc, char** argv);
static void GProcess_Run_METHOD(int argc, char** argv);
static void GProcess_Run_CHOICE(int argc, char** argv);
static void GProcess_Run_SQLITE(int argc, char** argv);
static void GProcess_Run_SAVE(int argc, char** argv);
static void GProcess_Run_LOAD(int argc, char** argv);
static void GProcess_Run_QUIT(int argc, char** argv);
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
    lObj->Delete = GProcess_Delete;
    lObj->Run = GProcess_Run;
    return lObj;
}
//===============================================
void GProcess_Delete() {
    GProcessO* lObj = GProcess();
    if(lObj != 0) {
        free(lObj);
    }
    m_GProcessO = 0;
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
    m_GProcessO->G_STATE = "S_INIT";
    while(1) {
        if(!strcmp(m_GProcessO->G_STATE, "S_ADMIN")) {GProcess_Run_ADMIN(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_INIT")) {GProcess_Run_INIT(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_METHOD")) {GProcess_Run_METHOD(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_CHOICE")) {GProcess_Run_CHOICE(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_SQLITE")) {GProcess_Run_SQLITE(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_SAVE")) {GProcess_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_LOAD")) {GProcess_Run_LOAD(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_QUIT")) {GProcess_Run_QUIT(argc, argv);}
        else break;
    }
}
//===============================================
static void GProcess_Run_ADMIN(int argc, char** argv) {
    printf("run_INIT\n");
    m_GProcessO->G_STATE = "S_END";
}
//===============================================
static void GProcess_Run_INIT(int argc, char** argv) {
    printf("\n");
    printf("C_ADMIN !!!\n");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    printf("\t%-2s : %s\n", "-i", "reinitialiser l'application");
    printf("\t%-2s : %s\n", "-a", "redemarrer l'application");
    printf("\t%-2s : %s\n", "-v", "valider les configurations");
    printf("\n");
    m_GProcessO->G_STATE = "S_LOAD";
}
//===============================================
static void GProcess_Run_METHOD(int argc, char** argv) {
    printf("C_ADMIN :\n");
    printf("\t%-2s : %s\n", "1", "S_SQLITE");
    printf("\n");
    m_GProcessO->G_STATE = "S_CHOICE";
}
//===============================================
static void GProcess_Run_CHOICE(int argc, char** argv) {
    char* lLast = "";
    printf("C_ADMIN (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; fgets(lAnswer, B_ANSWER, stdin); lAnswer[strlen(lAnswer)-1] = 0;
    if(!strcmp(lAnswer, "-q")) {m_GProcessO->G_STATE = "S_END";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GProcessO->G_STATE = "S_SQLITE";}
    //
}
//===============================================
static void GProcess_Run_SQLITE(int argc, char** argv) {
    printf("\n");
    printf("run_SQLITE\n");
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_SAVE(int argc, char** argv) {
    m_GProcessO->G_STATE = "S_QUIT";
}
//===============================================
static void GProcess_Run_LOAD(int argc, char** argv) {
    m_GProcessO->G_STATE = "S_METHOD";
}
//===============================================
static void GProcess_Run_QUIT(int argc, char** argv) {
    printf("\n");
    m_GProcessO->G_STATE = "S_END";
}
//===============================================
