//===============================================
#ifndef _GProcessList_
#define _GProcessList_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessListO GProcessListO;
//===============================================
struct _GProcessListO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessList_New();
void GProcessList_Delete();
GProcessO* GProcessList();
//===============================================
#endif
//===============================================
