//===============================================
#include "GKernelMenu.h"
#include "GKernelConnect.h"
#include "GConsole.h"
//===============================================
static GKernelMenuO* m_GKernelMenuO = 0;
//===============================================
static void GKernelMenu_Update();
//===============================================
GKernelMenuO* GKernelMenu_New() {
    GKernelMenuO* lObj = (GKernelMenuO*)malloc(sizeof(GKernelMenuO));
        
    lObj->Delete = GKernelMenu_Delete;
    lObj->Update = GKernelMenu_Update;
    return lObj;
}
//===============================================
void GKernelMenu_Delete() {
    GKernelMenuO* lObj = GKernelMenu();
    if(lObj != 0) {
        free(lObj);
    }
    m_GKernelMenuO = 0;
}
//===============================================
GKernelMenuO* GKernelMenu() {
    if(m_GKernelMenuO == 0) {
        m_GKernelMenuO = GKernelMenu_New();
    }
    return m_GKernelMenuO;
}
//===============================================
static void GKernelMenu_Update() {
    GKernelStatusEnum lStatus = GKernelConnect()->GetStatus();
    if(lStatus != GKERNEL_STATUS_CONNECT) return;
	GConsole()->Print("Je suis le gestionnaire de menu du Kernel [ 1 , 200 ms ]...\n");
}
//===============================================
