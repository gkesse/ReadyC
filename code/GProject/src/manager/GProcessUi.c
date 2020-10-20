//===============================================
#include "GProcessUi.h"
#include "GSQLiteUi.h"
#include "GGtkUi.h"
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
static void GProcessUi_Run_SOCKET(int argc, char** argv);
static void GProcessUi_Run_FILE(int argc, char** argv);
//===============================================
static void GProcessUi_Run_GTK(int argc, char** argv);
static void GProcessUi_Run_OPENCV(int argc, char** argv);
//===============================================
static void GProcessUi_Run_SQLITE(int argc, char** argv);
static void GProcessUi_Run_MYSQL(int argc, char** argv);
static void GProcessUi_Run_POSTGRESQL(int argc, char** argv);
static void GProcessUi_Run_FIREBIRD(int argc, char** argv);
static void GProcessUi_Run_MONGODB(int argc, char** argv);
//===============================================
static void GProcessUi_Run_GSOAP(int argc, char** argv);
static void GProcessUi_Run_DBUS(int argc, char** argv);
static void GProcessUi_Run_ZEROMQ(int argc, char** argv);
//===============================================
GProcessUiO* GProcessUi_New() {
    GProcessUiO* lObj = (GProcessUiO*)malloc(sizeof(GProcessUiO));
    lObj->Delete = GProcessUi_Delete;
    lObj->Run = GProcessUi_Run;
    return lObj;
}
//===============================================
void GProcessUi_Delete() {
    GProcessUiO* lObj = GProcessUi();
    if(lObj != 0) {
        free(lObj);
    }
    m_GProcessUiO = 0;
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
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_SOCKET")) {GProcessUi_Run_SOCKET(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_FILE")) {GProcessUi_Run_FILE(argc, argv);}
        //
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_GTK")) {GProcessUi_Run_GTK(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_OPENCV")) {GProcessUi_Run_OPENCV(argc, argv);}
        //
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_SQLITE")) {GProcessUi_Run_SQLITE(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_MYSQL")) {GProcessUi_Run_MYSQL(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_POSTGRESQL")) {GProcessUi_Run_POSTGRESQL(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_FIREBIRD")) {GProcessUi_Run_FIREBIRD(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_MONGODB")) {GProcessUi_Run_MONGODB(argc, argv);}
        //
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_GSOAP")) {GProcessUi_Run_GSOAP(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_DBUS")) {GProcessUi_Run_DBUS(argc, argv);}
        else if(!strcmp(m_GProcessUiO->G_STATE, "S_ZEROMQ")) {GProcessUi_Run_ZEROMQ(argc, argv);}
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
    printf("\n");
    m_GProcessUiO->G_STATE = "S_LOAD";
}
//===============================================
static void GProcessUi_Run_METHOD(int argc, char** argv) {
    printf("\n");
    printf("C_ADMIN :\n");
    printf("\t%-2s : %s\n", "1", "S_DATE");
    printf("\t%-2s : %s\n", "2", "S_THREAD");
    printf("\t%-2s : %s\n", "3", "S_SOCKET");
    printf("\t%-2s : %s\n", "4", "S_FILE");
    printf("\n");
    printf("\t%-2s : %s\n", "10", "S_GTK");
    printf("\t%-2s : %s\n", "11", "S_OPENCV");
    printf("\n");
    printf("\t%-2s : %s\n", "20", "S_SQLITE");
    printf("\t%-2s : %s\n", "21", "S_MYSQL");
    printf("\t%-2s : %s\n", "22", "S_POSTGRESQL");
    printf("\t%-2s : %s\n", "23", "S_FIREBIRD");
    printf("\t%-2s : %s\n", "24", "S_MONGODB");
    printf("\n");
    printf("\t%-2s : %s\n", "30", "S_GSOAP");
    printf("\t%-2s : %s\n", "31", "S_DBUS");
    printf("\t%-2s : %s\n", "32", "S_ZEROMQ");
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
    else if(!strcmp(lAnswer, "3")) {m_GProcessUiO->G_STATE = "S_SOCKET"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "4")) {m_GProcessUiO->G_STATE = "S_FILE"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
    else if(!strcmp(lAnswer, "10")) {m_GProcessUiO->G_STATE = "S_GTK"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "11")) {m_GProcessUiO->G_STATE = "S_OPENCV"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
    else if(!strcmp(lAnswer, "20")) {m_GProcessUiO->G_STATE = "S_SQLITE"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "21")) {m_GProcessUiO->G_STATE = "S_MYSQL"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "22")) {m_GProcessUiO->G_STATE = "S_POSTGRESQL"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "23")) {m_GProcessUiO->G_STATE = "S_FIREBIRD"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "24")) {m_GProcessUiO->G_STATE = "S_MONGODB"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
    else if(!strcmp(lAnswer, "30")) {m_GProcessUiO->G_STATE = "S_GSOAP"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "31")) {m_GProcessUiO->G_STATE = "S_DBUS"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "32")) {m_GProcessUiO->G_STATE = "S_ZEROMQ"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
}
//===============================================
static void GProcessUi_Run_SOCKET(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_FILE(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_GTK(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_OPENCV(int argc, char** argv) {
    GOpenCVUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_SQLITE(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_MYSQL(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_POSTGRESQL(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_FIREBIRD(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_MONGODB(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_GSOAP(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_DBUS(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessUiO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcessUi_Run_ZEROMQ(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
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
