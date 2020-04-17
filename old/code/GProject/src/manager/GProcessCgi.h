//===============================================
#ifndef _GProcessCgi_
#define _GProcessCgi_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessCgiO GProcessCgiO;
//===============================================
struct _GProcessCgiO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessCgi_New();
void GProcessCgi_Delete();
GProcessO* GProcessCgi();
//===============================================
#endif
//===============================================
