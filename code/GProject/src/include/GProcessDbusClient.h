//===============================================
#ifndef _GProcessDbusClient_
#define _GProcessDbusClient_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessDbusClientO GProcessDbusClientO;
//===============================================
struct _GProcessDbusClientO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessDbusClient_New();
void GProcessDbusClient_Delete();
GProcessO* GProcessDbusClient();
//===============================================
#endif
//===============================================
