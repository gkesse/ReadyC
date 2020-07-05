//===============================================
#ifndef _GProcessSemaphore_
#define _GProcessSemaphore_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSemaphoreO GProcessSemaphoreO;
//===============================================
struct _GProcessSemaphoreO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSemaphore_New();
void GProcessSemaphore_Delete();
GProcessO* GProcessSemaphore();
//===============================================
#endif
//===============================================
