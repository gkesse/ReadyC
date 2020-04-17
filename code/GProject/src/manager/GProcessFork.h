//===============================================
#ifndef _GProcessFork_
#define _GProcessFork_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessForkO GProcessForkO;
//===============================================
struct _GProcessForkO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessFork_New();
void GProcessFork_Delete();
GProcessO* GProcessFork();
//===============================================
#endif
//===============================================
