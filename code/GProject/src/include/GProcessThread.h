//===============================================
#ifndef _GProcessThread_
#define _GProcessThread_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessThreadO GProcessThreadO;
//===============================================
struct _GProcessThreadO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessThread_New();
void GProcessThread_Delete();
GProcessO* GProcessThread();
//===============================================
#endif
//===============================================
