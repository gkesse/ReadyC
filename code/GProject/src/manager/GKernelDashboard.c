//===============================================
#include "GKernelDashboard.h"
#include "GKernelConnect.h"
#include "GConsole.h"
//===============================================
static GKernelDashboardO* m_GKernelDashboardO = 0;
//===============================================
static void GKernelDashboard_Update();
//===============================================
GKernelDashboardO* GKernelDashboard_New() {
    GKernelDashboardO* lObj = (GKernelDashboardO*)malloc(sizeof(GKernelDashboardO));
        
    lObj->Delete = GKernelDashboard_Delete;
    lObj->Update = GKernelDashboard_Update;
    return lObj;
}
//===============================================
void GKernelDashboard_Delete() {
    GKernelDashboardO* lObj = GKernelDashboard();
    if(lObj != 0) {
        free(lObj);
    }
    m_GKernelDashboardO = 0;
}
//===============================================
GKernelDashboardO* GKernelDashboard() {
    if(m_GKernelDashboardO == 0) {
        m_GKernelDashboardO = GKernelDashboard_New();
    }
    return m_GKernelDashboardO;
}
//===============================================
static void GKernelDashboard_Update() {
    GKernelStatusEnum lStatus = GKernelConnect()->GetStatus();
    if(lStatus != GKERNEL_STATUS_CONNECT) return;
	GConsole()->Print("Je suis le gestionnaire de dashboard du Kernel [ 1 , 1000 ms ]...\n");
}
//===============================================
