//===============================================
#include "GTest.h"
#include "GAlarm.h"
#include "GBase.h"
#include "GConfig.h"
#include "GString.h"
#include "GClock.h"
#include "GSQLite.h"
#include "GMySQL.h"
#include "GDir.h"
#include "GShell.h"
#include "GThread2.h"
#include "GDebug.h"
//===============================================
#include "GTestBasic.h"
#include "GTestThreadUnix.h"
#include "GTestThreadWin.h"
#include "GTestSignalUnix.h"
#include "GTestSignalWin.h"
//===============================================
static GTestO* m_GTestO = 0;
//===============================================
static void GTest_Run(int argc, char** argv);
static void GTest_Default(int argc, char** argv);
static void GTest_Alarm(int argc, char** argv);
static void GTest_Base(int argc, char** argv);
static void GTest_Config(int argc, char** argv);
static void GTest_Debug(int argc, char** argv);
static void GTest_String(int argc, char** argv);
static void GTest_Clock(int argc, char** argv);
static void GTest_SQLite(int argc, char** argv);
static void GTest_MySQL(int argc, char** argv);
static void GTest_Dir(int argc, char** argv);
static void GTest_Shell(int argc, char** argv);
static void GTest_Thread(int argc, char** argv);
static void GTest_Thread2(int argc, char** argv);
static void GTest_Signal(int argc, char** argv);
//===============================================
static int GTest_OnDebug(char* buffer, int index, void* obj);
static void GTest_OnTimerThread(void* params);
//=============================================== 
#if defined (__WIN32)
unsigned __stdcall GTest_OnThread_1(void* params);
unsigned __stdcall GTest_OnThread_2(void* params);
static void WINAPI GTest_OnAlarm(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
static void GTest_ShellWin(int argc, char** argv);
#endif
//===============================================
#if defined (__unix)
static void* GTest_OnThread_1(void* params);
static void* GTest_OnThread_2(void* params);
static void GTest_OnAlarm(int sig);
static void GTest_ShellUnix(int argc, char** argv);
#endif
//===============================================
typedef struct _sGPerson sGPerson;
//===============================================
struct _sGPerson {
    int id;
    char* name;
    char* email;
    float coef;
};
//===============================================
GTestO* GTest_New() {
    GTestO* lObj = (GTestO*)malloc(sizeof(GTestO));
    lObj->Delete = GTest_Delete;
    lObj->Run = GTest_Run;
    return lObj;
}
//===============================================
void GTest_Delete() {
    GTestO* lObj = GTest();
    if(lObj != 0) {
        free(lObj);
    }
    m_GTestO = 0;
}
//===============================================
GTestO* GTest() {
    if(m_GTestO == 0) {
        m_GTestO = GTest_New();
    }
    return m_GTestO;
}
//===============================================
static void GTest_Run(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    for(int i = 2; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "basic")) {GTestBasic()->Run(argc, argv); return;}
        if(!strcmp(lKey, "alarm")) {GTest_Alarm(argc, argv); return;}
        if(!strcmp(lKey, "base")) {GTest_Base(argc, argv); return;}
        if(!strcmp(lKey, "config")) {GTest_Config(argc, argv); return;}
        if(!strcmp(lKey, "debug")) {GTest_Debug(argc, argv); return;}
        if(!strcmp(lKey, "string")) {GTest_String(argc, argv); return;}
        if(!strcmp(lKey, "clock")) {GTest_Clock(argc, argv); return;}
        if(!strcmp(lKey, "sqlite")) {GTest_SQLite(argc, argv); return;}
        if(!strcmp(lKey, "mysql")) {GTest_MySQL(argc, argv); return;}
        if(!strcmp(lKey, "dir")) {GTest_Dir(argc, argv); return;}
        if(!strcmp(lKey, "shell")) {GTest_Shell(argc, argv); return;}
        if(!strcmp(lKey, "thread")) {GTest_Thread(argc, argv); return;}
        if(!strcmp(lKey, "thread2")) {GTest_Thread2(argc, argv); return;}
        if(!strcmp(lKey, "signal")) {GTest_Signal(argc, argv); return;}
        break;
    }
    GTest_Default(argc, argv);
}
//===============================================
static void GTest_Default(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    printf("%s\n", __FUNCTION__);
}
//===============================================
static void GTest_Alarm(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    printf("%s\n", __FUNCTION__);
    GAlarm()->Timer("test", 1000);
    GAlarm()->Callback("test", GTest_OnAlarm);
    GAlarm()->Start("test");
    GAlarm()->Pause();
}
//===============================================
static void GTest_Base(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    int lDecimal;
    char lBinary[256];
    lDecimal = GBase()->FromBinary("11001100");
    GBase()->ToBinary(lDecimal, lBinary);
    printf("[%d]10 = [%s]2\n", lDecimal, lBinary);
}
//===============================================
static void GTest_Config(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GConfig()->SetData("name", "Gerard KESSE");
    GConfig()->SetData("email", "gerard.kesse@readydev.com");
    GConfig()->SetData("password", "12345678");
    GConfig()->Show();
}
//===============================================
static void GTest_Debug(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GDebug()->Write(2, 30, 5, "", 3, "Test du module debug", _EOA_);
    GDebug()->Write(2, 30, 5, "", 3, "Tracage d'un entier", _EOA_);
    GDebug()->Write(2, 30, 10, "", 30, -10, "Entier(int)", 3, " : ", 1, 2020, _EOA_);
    GDebug()->Write(2, 30, 5, "", 3, "Tracage d'un reel", _EOA_);
    GDebug()->Write(2, 30, 10, "", 30, -10, "Reel(double)", 3, " : ", 20, 2, 3.14, _EOA_);
    GDebug()->Write(2, 30, 5, "", 3, "Tracage d'une chaine de caracters", _EOA_);
    GDebug()->Write(2, 30, 10, "", 30, -10, "Chaine(char*)", 3, " : ", 3, "www.readydev.com", _EOA_);
    GDebug()->Write(2, 30, 5, "", 3, "Tracage d'une structure complexe", _EOA_);
    GDebug()->Write(2, 30, 10, "", 3, "Creation de la structure", _EOA_);

    sGPerson lPersons[] = {
        {1, "Gerard KESSE", "gerard.kesse@rdev.com", 25.25},
        {2, "Deborah YOBOUE", "deborah.yoboue@rdev.com", 55.25},
        {3, "Robins KESSE", "robins.kesse@rdev.com", 75.25},
        {0, 0, 0, 0}
    };
    
    GDebug()->Write(2, 30, 10, "", 3, "Tracage de la structure", _EOA_);
    GDebug()->Write(2, 30, 10, "", 30, -10, "Structure(void*)", 3, " : \n\n", 4, GTest_OnDebug, lPersons, _EOA_);
}
//===============================================
static void GTest_String(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char lTrim[256], lReplace[256];
    
    GString()->Trim("\n\t\r    Voici ma chaine    \n\t\r", lTrim);
    GString()->Replace("C:/Users/Admin/.readydev/readyc/data/debug", lReplace, "/", "\\");
    
    printf("lTrim : >%s<\n", lTrim);
    printf("lReplace : >%s<\n", lReplace);
}
//===============================================
static void GTest_Clock(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    ulong lDelay = 1000000000;
    GClock()->Start("clock");
    for(int i = 0; i< lDelay; i++);
    GClock()->End("clock");
    double lTime = GClock()->Time("clock");
    printf("Temps ecoule : %.0f (ms)\n", lTime);
    double lTimeFor = (double)(lTime * 1000 * 1000) / lDelay;
    printf("Temps ecoule (for) : %.2f (ns)\n", lTimeFor);
}
//===============================================
static void GTest_SQLite(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GSQLite()->Version();
    GSQLite()->Open("db", "data/sqlite/db.dat");
}
//===============================================
static void GTest_MySQL(int argc, char** argv) {
#if defined(_GUSE_MYSQL_ON_)
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMySQL()->Version();
#endif
}
//===============================================
static void GTest_Dir(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char lPath[256];
    GDir()->Path("data/sqlite/db.dat", lPath);
    printf("%s\n", lPath);
    GDir()->Name(lPath, lPath);
    printf("%s\n", lPath);
}
//===============================================
static void GTest_Shell(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
#if defined(__WIN32)
	GTest_ShellWin(argc, argv);
#elif defined(__unix)
	GTest_ShellUnix(argc, argv);
#endif
}
//===============================================
static void GTest_Thread(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
#if defined(__WIN32)
    GTestThreadWin()->Run(argc, argv);
#elif defined(__unix)
    GTestThreadUnix()->Run(argc, argv);
#endif
}
//===============================================
static void GTest_Thread2(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
#if defined(__WIN32)
    GDebug()->Write(2, 3, "\nDebut de la concurrence\n", _EOA_);
    GThread2()->Create("thread_1", GTest_OnThread_1, 0);
    GThread2()->Create("thread_2", GTest_OnThread_2, 0);
    GThread2()->Join("thread_1", INFINITE);
    GThread2()->Join("thread_2", INFINITE);
    GThread2()->Close("thread_1");
    GThread2()->Close("thread_2");
    GDebug()->Write(2, 3, "\nFin de la concurrence\n", _EOA_);
#elif defined(__unix)
    GDebug()->Write(2, 3, "\nDebut de la concurrence\n", _EOA_);
    GThread2()->Create("thread_1", GTest_OnThread_1, 0);
    GThread2()->Create("thread_2", GTest_OnThread_2, 0);
    GThread2()->Join("thread_1", 0);
    GThread2()->Join("thread_2", 0);
    GDebug()->Write(2, 3, "\nFin de la concurrence\n", _EOA_);
#endif
}
//===============================================
static void GTest_Signal(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
#if defined(__WIN32)
    GTestSignalWin()->Run(argc, argv);
#elif defined(__unix)
    GTestSignalUnix()->Run(argc, argv);
#endif
}
//===============================================
static int GTest_OnDebug(char* buffer, int index, void* obj) {
    int lIndex = index;
    sGPerson* lPersons = (sGPerson*)obj;
    lIndex += sprintf(&buffer[lIndex], "%-10s%-2s | %-14s | %-23s | %s\n", " ", "id", "name", "email", "coef");
    int i = 0;
    while(1) {
        sGPerson* lPerson = &lPersons[i++];
        int lId = lPerson->id;
        if(lId == 0) break;
        char* lName = lPerson->name;
        char* lEmail = lPerson->email;
        float lCoef = lPerson->coef;
        lIndex += sprintf(&buffer[lIndex], "%-10s%-2d | %-14s | %-23s | %.2f\n", " ", lId, lName, lEmail, lCoef);
    }
    return lIndex - index;
}
//===============================================
#if defined (__WIN32)
//===============================================
unsigned __stdcall GTest_OnThread_1(void* params) {
    for(int i = 0; i < 10; i++) {
        GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
        sleep(1);
    }
    return 0;
}
//===============================================
unsigned __stdcall GTest_OnThread_2(void* params) {
    for(int i = 0; i < 10; i++) {
        GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
        sleep(1);
    }
    return 0;
}
//===============================================
static void WINAPI GTest_OnAlarm(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
}
//===============================================
static void GTest_ShellWin(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	char lCommand[256];
	char lOuput[256];
	sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
	GShell()->Run(lCommand, lOuput, 255, 1);
	printf("%s\n", lOuput);
}
//===============================================
#elif defined (__unix)
//===============================================
void* GTest_OnThread_1(void* params) {
    for(int i = 0; i < 10; i++) {
        GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
        sleep(1);
    }
    GThread2()->Close("thread_1");
}
//===============================================
void* GTest_OnThread_2(void* params) {
    for(int i = 0; i < 10; i++) {
        GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
        sleep(1);
    }
    GThread2()->Close("thread_2");
}
//===============================================
static void GTest_OnAlarm(int sig) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GAlarm()->Restart("test");
}
//===============================================
static void GTest_ShellUnix(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
	char lCommand[256];
	char lOuput[256];
	sprintf(lCommand, "%s", "echo -n $HOME");
	GShell()->Run(lCommand, lOuput, 255, 0);
	printf("%s\n", lOuput);
}
//===============================================
#endif
//===============================================
