//===============================================
#ifndef _GKernelMenu_
#define _GKernelMenu_
//===============================================
#include "GInclude.h"
#include "GEnum.h"
//===============================================
typedef struct _GKernelMenuO GKernelMenuO;
//===============================================
struct _GKernelMenuO {
    void (*Delete)();
    void (*Update)();
};
//===============================================
GKernelMenuO* GKernelMenu_New();
void GKernelMenu_Delete();
GKernelMenuO* GKernelMenu();
//===============================================
#endif
//===============================================
