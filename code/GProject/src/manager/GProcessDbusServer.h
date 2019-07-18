//===============================================
#ifndef _GProcessDbusServer_
#define _GProcessDbusServer_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessDbusServerO GProcessDbusServerO;
//===============================================
struct _GProcessDbusServerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessDbusServer_New();
void GProcessDbusServer_Delete();
GProcessO* GProcessDbusServer();
//===============================================
#endif
//===============================================
