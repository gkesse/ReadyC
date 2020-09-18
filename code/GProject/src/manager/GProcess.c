//===============================================
#include "GProcess.h"
#include "GSQLiteUi.h"
#include "GDateUi.h"
#include "GGtkUi.h"
#include "GOpenCVUi.h"
#include "GConfig.h"
#include "GManager.h"
//===============================================
#define B_ANSWER (256)
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Run(int argc, char** argv);
//===============================================
static void GProcess_Run_INIT(int argc, char** argv);
static void GProcess_Run_METHOD(int argc, char** argv);
static void GProcess_Run_CHOICE(int argc, char** argv);
static void GProcess_Run_SAVE(int argc, char** argv);
static void GProcess_Run_LOAD(int argc, char** argv);
//===============================================
static void GProcess_Run_DATE(int argc, char** argv);
static void GProcess_Run_THREAD(int argc, char** argv);
static void GProcess_Run_SOCKET(int argc, char** argv);
static void GProcess_Run_FILE(int argc, char** argv);
//===============================================
static void GProcess_Run_GTK(int argc, char** argv);
static void GProcess_Run_OPENCV(int argc, char** argv);
//===============================================
static void GProcess_Run_SQLITE(int argc, char** argv);
static void GProcess_Run_MYSQL(int argc, char** argv);
static void GProcess_Run_POSTGRESQL(int argc, char** argv);
static void GProcess_Run_FIREBIRD(int argc, char** argv);
static void GProcess_Run_MONGODB(int argc, char** argv);
//===============================================
static void GProcess_Run_GSOAP(int argc, char** argv);
static void GProcess_Run_DBUS(int argc, char** argv);
static void GProcess_Run_ZEROMQ(int argc, char** argv);
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
        if(!strcmp(m_GProcessO->G_STATE, "S_INIT")) {GProcess_Run_INIT(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_METHOD")) {GProcess_Run_METHOD(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_CHOICE")) {GProcess_Run_CHOICE(argc, argv);}
        //
        else if(!strcmp(m_GProcessO->G_STATE, "S_DATE")) {GProcess_Run_DATE(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_THREAD")) {GProcess_Run_THREAD(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_SOCKET")) {GProcess_Run_SOCKET(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_FILE")) {GProcess_Run_FILE(argc, argv);}
        //
        else if(!strcmp(m_GProcessO->G_STATE, "S_GTK")) {GProcess_Run_GTK(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_OPENCV")) {GProcess_Run_OPENCV(argc, argv);}
        //
        else if(!strcmp(m_GProcessO->G_STATE, "S_SQLITE")) {GProcess_Run_SQLITE(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_MYSQL")) {GProcess_Run_MYSQL(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_POSTGRESQL")) {GProcess_Run_POSTGRESQL(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_FIREBIRD")) {GProcess_Run_FIREBIRD(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_MONGODB")) {GProcess_Run_MONGODB(argc, argv);}
        //
        else if(!strcmp(m_GProcessO->G_STATE, "S_GSOAP")) {GProcess_Run_GSOAP(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_DBUS")) {GProcess_Run_DBUS(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_ZEROMQ")) {GProcess_Run_ZEROMQ(argc, argv);}
        //
        else if(!strcmp(m_GProcessO->G_STATE, "S_SAVE")) {GProcess_Run_SAVE(argc, argv);}
        else if(!strcmp(m_GProcessO->G_STATE, "S_LOAD")) {GProcess_Run_LOAD(argc, argv);}
        else break;
    }
}
//===============================================
static void GProcess_Run_INIT(int argc, char** argv) {
    printf("\n");
    printf("C_ADMIN !!!\n");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    printf("\n");
    m_GProcessO->G_STATE = "S_LOAD";
}
//===============================================
static void GProcess_Run_METHOD(int argc, char** argv) {
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
    m_GProcessO->G_STATE = "S_CHOICE";
}
//===============================================
static void GProcess_Run_CHOICE(int argc, char** argv) {
    char* lLast = GConfig()->GetData("G_ADMIN_ID");
    printf("C_ADMIN (%s) ? ", lLast);
    char lAnswer[B_ANSWER+1]; GManager()->ReadLine(lAnswer, B_ANSWER);
    if(!strcmp(lAnswer, "")) {strcpy(lAnswer, lLast);}
    if(!strcmp(lAnswer, "-q")) {m_GProcessO->G_STATE = "S_END";}
    //
    else if(!strcmp(lAnswer, "1")) {m_GProcessO->G_STATE = "S_DATE"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "2")) {m_GProcessO->G_STATE = "S_THREAD"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "3")) {m_GProcessO->G_STATE = "S_SOCKET"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "4")) {m_GProcessO->G_STATE = "S_FILE"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
    else if(!strcmp(lAnswer, "10")) {m_GProcessO->G_STATE = "S_GTK"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "11")) {m_GProcessO->G_STATE = "S_OPENCV"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
    else if(!strcmp(lAnswer, "20")) {m_GProcessO->G_STATE = "S_SQLITE"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "21")) {m_GProcessO->G_STATE = "S_MYSQL"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "22")) {m_GProcessO->G_STATE = "S_POSTGRESQL"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "23")) {m_GProcessO->G_STATE = "S_FIREBIRD"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "24")) {m_GProcessO->G_STATE = "S_MONGODB"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
    else if(!strcmp(lAnswer, "30")) {m_GProcessO->G_STATE = "S_GSOAP"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "31")) {m_GProcessO->G_STATE = "S_DBUS"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    else if(!strcmp(lAnswer, "32")) {m_GProcessO->G_STATE = "S_ZEROMQ"; GConfig()->SetData("G_ADMIN_ID", lAnswer);}
    //
}
//===============================================
static void GProcess_Run_DATE(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_THREAD(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_SOCKET(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_FILE(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_GTK(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_OPENCV(int argc, char** argv) {
    GOpenCVUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_SQLITE(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_MYSQL(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_POSTGRESQL(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_FIREBIRD(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_MONGODB(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_GSOAP(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_DBUS(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_ZEROMQ(int argc, char** argv) {
    GSQLiteUi()->Run(argc, argv);
    m_GProcessO->G_STATE = "S_SAVE";
}
//===============================================
static void GProcess_Run_SAVE(int argc, char** argv) {
    GConfig()->SaveData("G_ADMIN_ID");
    m_GProcessO->G_STATE = "S_END";
}
//===============================================
static void GProcess_Run_LOAD(int argc, char** argv) {
    GConfig()->LoadData("G_ADMIN_ID");
    m_GProcessO->G_STATE = "S_METHOD";
}
//===============================================
