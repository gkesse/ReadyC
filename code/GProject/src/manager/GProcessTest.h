//===============================================
#ifndef _GProcessTest_
#define _GProcessTest_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessTestO GProcessTestO;
//===============================================
struct _GProcessTestO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessTest_New();
void GProcessTest_Delete();
GProcessO* GProcessTest();
//===============================================
#endif
//===============================================
