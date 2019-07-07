//===============================================
#include "GProcess.h"
#include "GProcessConsole.h"
#include "GProcessKeyboard.h"
#include "GProcessMap.h"
#include "GProcessConfig.h"
#include "GProcessSocketServer.h"
#include "GProcessSocketClient.h"
#include "GProcessSoapClient.h"
#include "GProcessSoapServer.h"
#include "GProcessCgi.h"
#include "GProcessDatabase.h"
#include "GProcessGtk.h"
#include "GString2.h"
#include "GConfig.h"
//===============================================
GProcessO* GProcess_New() {
    GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
    lObj->m_child = 0;
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
<<<<<<< HEAD
    if(GString()->IsEqual(lKey, "CONSOLE")) return GProcessConsole();
    if(GString()->IsEqual(lKey, "KEYBOARD")) return GProcessKeyboard();
    if(GString()->IsEqual(lKey, "MAP")) return GProcessMap();
    if(GString()->IsEqual(lKey, "CONFIG")) return GProcessConfig();
    if(GString()->IsEqual(lKey, "SOCKET_SERVER")) return GProcessSocketServer();
    if(GString()->IsEqual(lKey, "SOCKET_CLIENT")) return GProcessSocketClient();
    if(GString()->IsEqual(lKey, "SOAP_CLIENT")) return GProcessSoapClient();
    if(GString()->IsEqual(lKey, "SOAP_SERVER")) return GProcessSoapServer();
    if(GString()->IsEqual(lKey, "CGI")) return GProcessCgi();
   if(GString()->IsEqual(lKey, "DATABASE")) return GProcessDatabase();
=======
    if(GString2()->IsEqual(lKey, "CONSOLE")) return GProcessConsole();
    if(GString2()->IsEqual(lKey, "KEYBOARD")) return GProcessKeyboard();
    if(GString2()->IsEqual(lKey, "MAP")) return GProcessMap();
    if(GString2()->IsEqual(lKey, "CONFIG")) return GProcessConfig();
    if(GString2()->IsEqual(lKey, "SOCKET_SERVER")) return GProcessSocketServer();
    if(GString2()->IsEqual(lKey, "SOCKET_CLIENT")) return GProcessSocketClient();
    if(GString2()->IsEqual(lKey, "SOAP_CLIENT")) return GProcessSoapClient();
    if(GString2()->IsEqual(lKey, "SOAP_SERVER")) return GProcessSoapServer();
    if(GString2()->IsEqual(lKey, "DATABASE")) return GProcessDatabase();
    if(GString2()->IsEqual(lKey, "GTK")) return GProcessGtk();
>>>>>>> e856714f5bde9182b2f094384f4252baeff32698
    return GProcessConsole();
}
//===============================================
