//===============================================
#ifndef _GProcessMap_
#define _GProcessMap_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessMapO GProcessMapO;
//===============================================
struct _GProcessMapO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessMap_New();
void GProcessMap_Delete(GProcessO* obj);
GProcessO* GProcessMap();
//===============================================
#endif
//===============================================
