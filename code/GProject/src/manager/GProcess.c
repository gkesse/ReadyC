//===============================================
#include "GProcess.h"
#include "GProcessConsole.h"
#include "GProcessKeyboard.h"
#include "GProcessMap.h"
#include "GProcessConfig.h"
#include "GProcessSocketServer.h"
#include "GProcessSocketClient.h"
#include "GProcessDatabase.h"
#include "GProcessSoap.h"
#include "GString.h"
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
    if(GString()->IsEqual(lKey, "CONSOLE")) return GProcessConsole();
    if(GString()->IsEqual(lKey, "KEYBOARD")) return GProcessKeyboard();
    if(GString()->IsEqual(lKey, "MAP")) return GProcessMap();
    if(GString()->IsEqual(lKey, "CONFIG")) return GProcessConfig();
    if(GString()->IsEqual(lKey, "SOCKET_SERVER")) return GProcessSocketServer();
    if(GString()->IsEqual(lKey, "SOCKET_CLIENT")) return GProcessSocketClient();
    if(GString()->IsEqual(lKey, "DATABASE")) return GProcessDatabase();
    if(GString()->IsEqual(lKey, "SOAP")) return GProcessSoap();
    return GProcessConsole();
}
//===============================================
