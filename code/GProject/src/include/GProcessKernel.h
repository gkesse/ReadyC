//===============================================
#ifndef _GProcessKernel_
#define _GProcessKernel_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessKernelO GProcessKernelO;
//===============================================
struct _GProcessKernelO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessKernel_New();
void GProcessKernel_Delete();
GProcessO* GProcessKernel();
//===============================================
#endif
//===============================================
