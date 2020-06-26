//===============================================
#if 0
//===============================================
#include "GProcess.h"
#include "GProcessHelp.h"
#include "GProcessArgTable.h"
#include "GProcessConsole.h"
#include "GProcessKeyboard.h"
#include "GProcessList.h"
#include "GProcessMap.h"
#include "GProcessConfig.h"
#include "GProcessFork.h"
#include "GProcessSocketServer.h"
#include "GProcessSocketClient.h"
#include "GProcessSocketUnixServer.h"
#include "GProcessSocketUnixClient.h"
#include "GProcessSocketUnixServerUdp.h"
#include "GProcessSocketUnixClientUdp.h"
//#include "GProcessSocketUnixServerFile.h"
//#include "GProcessSocketUnixClientFile.h"
#include "GProcessSocketWindowsServer.h"
#include "GProcessSocketWindowsClient.h"
#include "GProcessSoapClient.h"
#include "GProcessSoapServer.h"
#include "GProcessCgi.h"
#include "GProcessDatabase.h"
#include "GProcessMySQL.h"
#include "GProcessGtk.h"
#include "GProcessThread.h"
#include "GProcessMutex.h"
#include "GProcessSemaphore.h"
#include "GProcessRaceCondition.h"
#include "GProcessScheduler.h"
#include "GProcessKernel.h"
#include "GProcessTimer.h"
#include "GProcessTimerInterval.h"
#include "GProcessClock.h"
#include "GProcessAlarmSignal.h"
#include "GString2.h"
#include "GConfig.h"
//===============================================
static int GProcess_Fork();
static void GProcess_Wait();
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
    lObj->m_child = 0;
    lObj->Fork = GProcess_Fork;
    lObj->Wait = GProcess_Wait;
    return lObj;
}
//===============================================
void GProcess_Delete(GProcessO* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GProcessO* GProcess() {
    char* lKey = GConfig()->GetData("PROCESS");
    if(GString2()->IsEqual(lKey, "HELP")) return GProcessHelp();
    if(GString2()->IsEqual(lKey, "ARG_TABLE")) return GProcessArgTable();
    if(GString2()->IsEqual(lKey, "CONSOLE")) return GProcessConsole();
    if(GString2()->IsEqual(lKey, "KEYBOARD")) return GProcessKeyboard();
    if(GString2()->IsEqual(lKey, "LIST")) return GProcessList();
    if(GString2()->IsEqual(lKey, "MAP")) return GProcessMap();
    if(GString2()->IsEqual(lKey, "CONFIG")) return GProcessConfig();
    //if(GString2()->IsEqual(lKey, "FORK")) return GProcessFork();
    //if(GString2()->IsEqual(lKey, "SOCKET_SERVER")) return GProcessSocketServer();
    //if(GString2()->IsEqual(lKey, "SOCKET_CLIENT")) return GProcessSocketClient();
    //if(GString2()->IsEqual(lKey, "SOCKET_UNIX_SERVER")) return GProcessSocketUnixServer();
    //if(GString2()->IsEqual(lKey, "SOCKET_UNIX_CLIENT")) return GProcessSocketUnixClient();
    //if(GString2()->IsEqual(lKey, "SOCKET_UNIX_SERVER_UDP")) return GProcessSocketUnixServerUdp();
    //if(GString2()->IsEqual(lKey, "SOCKET_UNIX_CLIENT_UDP")) return GProcessSocketUnixClientUdp();
    //if(GString2()->IsEqual(lKey, "SOCKET_UNIX_SERVER_FILE")) return GProcessSocketUnixServerFile();
    //if(GString2()->IsEqual(lKey, "SOCKET_UNIX_CLIENT_FILE")) return GProcessSocketUnixClientFile();
    //if(GString2()->IsEqual(lKey, "SOCKET_WINDOWS_SERVER")) return GProcessSocketWindowsServer();
    //if(GString2()->IsEqual(lKey, "SOCKET_WINDOWS_CLIENT")) return GProcessSocketWindowsClient();
    //if(GString2()->IsEqual(lKey, "SOAP_CLIENT")) return GProcessSoapClient();
    //if(GString2()->IsEqual(lKey, "SOAP_SERVER")) return GProcessSoapServer();
    if(GString2()->IsEqual(lKey, "CGI")) return GProcessCgi();
    if(GString2()->IsEqual(lKey, "DATABASE")) return GProcessDatabase();
    if(GString2()->IsEqual(lKey, "MYSQL")) return GProcessMySQL();
    if(GString2()->IsEqual(lKey, "GTK")) return GProcessGtk();
    if(GString2()->IsEqual(lKey, "THREAD")) return GProcessThread();
    if(GString2()->IsEqual(lKey, "MUTEX")) return GProcessMutex();
    if(GString2()->IsEqual(lKey, "SEMAPHORE")) return GProcessSemaphore();
    if(GString2()->IsEqual(lKey, "RACE_CONDITION")) return GProcessRaceCondition();
    if(GString2()->IsEqual(lKey, "SCHEDULER")) return GProcessScheduler();
    if(GString2()->IsEqual(lKey, "KERNEL")) return GProcessKernel();
    if(GString2()->IsEqual(lKey, "TIMER")) return GProcessTimer();
    if(GString2()->IsEqual(lKey, "TIMER_INTERVAL")) return GProcessTimerInterval();
    if(GString2()->IsEqual(lKey, "CLOCK")) return GProcessClock();
    if(GString2()->IsEqual(lKey, "ALARM_SIGNAL")) return GProcessAlarmSignal();
    return GProcessHelp();
}
//===============================================
static int GProcess_Fork() {
    int lPid = 0; //fork();
    return lPid;
}
//===============================================
static void GProcess_Wait() {
    //wait(0);
}
//===============================================
#endif
//===============================================