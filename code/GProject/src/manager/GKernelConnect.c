//===============================================
#include "GKernelConnect.h"
#include "GConsole.h"
//===============================================
static GKernelConnectO* m_GKernelConnectO = 0;
//===============================================
static void GKernelConnect_Update();
static GKernelStatusEnum GKernelConnect_GetStatus();
//===============================================
GKernelConnectO* GKernelConnect_New() {
    GKernelConnectO* lObj = (GKernelConnectO*)malloc(sizeof(GKernelConnectO));
    
    lObj->m_status = GKERNEL_STATUS_UNKNOWN;
    
    lObj->Delete = GKernelConnect_Delete;
    lObj->Update = GKernelConnect_Update;
    lObj->GetStatus = GKernelConnect_GetStatus;
    return lObj;
}
//===============================================
void GKernelConnect_Delete() {
    GKernelConnectO* lObj = GKernelConnect();
    if(lObj != 0) {
        free(lObj);
    }
    m_GKernelConnectO = 0;
}
//===============================================
GKernelConnectO* GKernelConnect() {
    if(m_GKernelConnectO == 0) {
        m_GKernelConnectO = GKernelConnect_New();
    }
    return m_GKernelConnectO;
}
//===============================================
static void GKernelConnect_Update() {
	GConsole()->Print("Je suis le gestionnaire de connexion du Kernel [ 1 , 200 ms ]...\n");
}
//===============================================
static GKernelStatusEnum GKernelConnect_GetStatus() {
    GKernelStatusEnum lStatus = m_GKernelConnectO->m_status;
    return lStatus;
}
//===============================================
