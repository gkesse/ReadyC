//===============================================
#ifndef _GProcessGtk_
#define _GProcessGtk_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessGtkO GProcessGtkO;
//===============================================
struct _GProcessGtkO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessGtk_New();
void GProcessGtk_Delete();
GProcessO* GProcessGtk();
//===============================================
#endif
//===============================================
