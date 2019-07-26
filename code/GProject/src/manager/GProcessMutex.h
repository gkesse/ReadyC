//===============================================
#ifndef _GProcessMutex_
#define _GProcessMutex_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessMutexO GProcessMutexO;
//===============================================
struct _GProcessMutexO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessMutex_New();
void GProcessMutex_Delete();
GProcessO* GProcessMutex();
//===============================================
#endif
//===============================================
