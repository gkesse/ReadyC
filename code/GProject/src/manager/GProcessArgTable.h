//===============================================
#ifndef _GProcessArgTable_
#define _GProcessArgTable_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessArgTableO GProcessArgTableO;
//===============================================
struct _GProcessArgTableO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessArgTable_New();
void GProcessArgTable_Delete();
GProcessO* GProcessArgTable();
//===============================================
#endif
//===============================================
