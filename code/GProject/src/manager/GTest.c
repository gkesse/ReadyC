//===============================================
#include "GTest.h"
#include "GTestBasic.h"
#include "GAlarm2.h"
#include "GBase.h"
#include "GDebug.h"
#include "GConfig.h"
//===============================================
static GTestO* m_GTestO = 0;
//===============================================
static void GTest_Run(int argc, char** argv);
static void GTest_Default(int argc, char** argv);
static void GTest_Alarm(int argc, char** argv);
static void GTest_Base(int argc, char** argv);
static void GTest_Config(int argc, char** argv);
static void GTest_Debug(int argc, char** argv);
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
    GDebug()->Sep();
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
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
