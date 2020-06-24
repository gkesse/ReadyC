//===============================================
#include "GTest.h"
#include "GTestBasic.h"
#include "GAlarm2.h"
#include "GBase.h"
#include "GConfig.h"
#include "GString3.h"
#include "GDebug.h"
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
//===============================================
static int GTest_OnDebug(char* buffer, int index, void* obj);
//=============================================== 
#if defined (__WIN32)
//===============================================
static void WINAPI GTest_OnAlarm(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
//===============================================
#elif defined (__unix)
//===============================================
static void GTest_OnAlarm(int sig);
//===============================================
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
    free(lObj);
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
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    for(int i = 2; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "basic")) {GTestBasic()->Run(argc, argv); return;}
        if(!strcmp(lKey, "alarm")) {GTest_Alarm(argc, argv); return;}
        if(!strcmp(lKey, "base")) {GTest_Base(argc, argv); return;}
        if(!strcmp(lKey, "config")) {GTest_Config(argc, argv); return;}
        if(!strcmp(lKey, "debug")) {GTest_Debug(argc, argv); return;}
        if(!strcmp(lKey, "string")) {GTest_String(argc, argv); return;}
        break;
    }
    GTest_Default(argc, argv);
}
//===============================================
static void GTest_Default(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    printf("%s\n", __FUNCTION__);
}
//===============================================
static void GTest_Alarm(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    printf("%s\n", __FUNCTION__);
    GAlarm2()->Timer("test", 1000);
    GAlarm2()->Callback("test", GTest_OnAlarm);
    GAlarm2()->Start("test");
    GAlarm2()->Pause();
}
//===============================================
static void GTest_Base(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lDecimal;
    char lBinary[256];
    lDecimal = GBase()->FromBinary("11001100");
    GBase()->ToBinary(lDecimal, lBinary);
    printf("[%d]_10 = [%s]_2\n", lDecimal, lBinary);
}
//===============================================
static void GTest_Config(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GConfig()->SetData("name", "Gerard KESSE");
    GConfig()->SetData("email", "gerard.kesse@readydev.com");
    GConfig()->SetData("password", "12345678");
    GConfig()->Show();
}
//===============================================
static void GTest_Debug(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GDebug()->Trace(1, 30, 5, "", 3, "Test du module debug", _EOT_);
    GDebug()->Trace(1, 30, 5, "", 3, "Tracage d'un entier", _EOT_);
    GDebug()->Trace(1, 30, 10, "", 30, -10, "Entier(int)", 3, " : ", 1, 2020, _EOT_);
    GDebug()->Trace(1, 30, 5, "", 3, "Tracage d'un reel", _EOT_);
    GDebug()->Trace(1, 30, 10, "", 30, -10, "Reel(double)", 3, " : ", 20, 2, 3.14, _EOT_);
    GDebug()->Trace(1, 30, 5, "", 3, "Tracage d'une chaine de caracters", _EOT_);
    GDebug()->Trace(1, 30, 10, "", 30, -10, "Chaine(char*)", 3, " : ", 3, "www.readydev.com", _EOT_);
    GDebug()->Trace(1, 30, 5, "", 3, "Tracage d'une structure complexe", _EOT_);
    GDebug()->Trace(1, 30, 10, "", 3, "Creation de la structure", _EOT_);

    sGPerson lPersons[] = {
        {1, "Gerard KESSE", "gerard.kesse@rdev.com", 25.25},
        {2, "Deborah YOBOUE", "deborah.yoboue@rdev.com", 55.25},
        {3, "Robins KESSE", "robins.kesse@rdev.com", 75.25},
        {0, 0, 0, 0}
    };
    
    GDebug()->Trace(1, 30, 10, "", 3, "Tracage de la structure", _EOT_);
    GDebug()->Trace(1, 30, 10, "", 30, -10, "Structure(void*)", 3, " : \n\n", 4, GTest_OnDebug, lPersons, _EOT_);
}
//===============================================
static void GTest_String(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char lTrim[256];
    GString3()->Trim("\n\t\r    Voici ma chaine    ", lTrim);
    printf(">%s<\n", lTrim);
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
static void WINAPI GTest_OnAlarm(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
#elif defined (__unix)
//===============================================
static void GTest_OnAlarm(int sig) {
    printf("%s\n", __FUNCTION__);
    GAlarm2()->Restart("test");
}
//===============================================
#endif
//===============================================
