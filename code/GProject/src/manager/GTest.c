//===============================================
#include "GTest.h"
#include "GTestBasic.h"
#include "GAlarm2.h"
#include "GBase.h"
#include "GConfig2.h"
//===============================================
static GTestO* m_GTestO = 0;
//===============================================
static void GTest_Run(int argc, char** argv);
static void GTest_Default(int argc, char** argv);
static void GTest_Alarm(int argc, char** argv);
static void WINAPI GTest_OnAlarm(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
static void GTest_Base(int argc, char** argv);
static void GTest_Config(int argc, char** argv);
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
    for(int i = 2; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "basic")) {GTestBasic()->Run(argc, argv); return;}
        if(!strcmp(lKey, "alarm")) {GTest_Alarm(argc, argv); return;}
        if(!strcmp(lKey, "base")) {GTest_Base(argc, argv); return;}
        if(!strcmp(lKey, "config")) {GTest_Config(argc, argv); return;}
        break;
    }
    GTest_Default(argc, argv);
}
//===============================================
static void GTest_Default(int argc, char** argv) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
static void GTest_Alarm(int argc, char** argv) {
    printf("%s\n", __FUNCTION__);
    GAlarm2()->Timer("test", 1000);
    GAlarm2()->Callback("test", GTest_OnAlarm);
    GAlarm2()->Start("test");
    while(1) Sleep(3000);
}
//===============================================
static void WINAPI GTest_OnAlarm(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
static void GTest_Base(int argc, char** argv) {
    int lDecimal;
    char lBinary[256];
    lDecimal = GBase()->FromBinary("11001100");
    GBase()->ToBinary(lDecimal, lBinary);
    printf("[%d]_10 = [%s]_2\n", lDecimal, lBinary);
}
//===============================================
static void GTest_Config(int argc, char** argv) {
    GConfig2()->SetData("name", "Gerard KESSE");
    GConfig2()->SetData("email", "gerard.kesse@readydev.com");
    GConfig2()->SetData("password", "12345678");
    GConfig2()->Show();
}
//===============================================
