//===============================================
#ifndef _GKernelDashboard_
#define _GKernelDashboard_
//===============================================
#include "GInclude.h"
#include "GEnum.h"
//===============================================
typedef struct _GKernelDashboardO GKernelDashboardO;
//===============================================
struct _GKernelDashboardO {
    void (*Delete)();
    void (*Update)();
};
//===============================================
GKernelDashboardO* GKernelDashboard_New();
void GKernelDashboard_Delete();
GKernelDashboardO* GKernelDashboard();
//===============================================
#endif
//===============================================
