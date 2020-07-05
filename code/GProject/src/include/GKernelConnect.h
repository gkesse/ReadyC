//===============================================
#ifndef _GKernelConnect_
#define _GKernelConnect_
//===============================================
#include "GInclude.h"
#include "GEnum.h"
//===============================================
typedef struct _GKernelConnectO GKernelConnectO;
//===============================================
struct _GKernelConnectO {
    void (*Delete)();
    void (*Update)();
    GKernelStatusEnum (*GetStatus)();
    GKernelStatusEnum m_status;
};
//===============================================
GKernelConnectO* GKernelConnect_New();
void GKernelConnect_Delete();
GKernelConnectO* GKernelConnect();
//===============================================
#endif
//===============================================
