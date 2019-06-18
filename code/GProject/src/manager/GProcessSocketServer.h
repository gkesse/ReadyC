//===============================================
#ifndef _GProcessSocketServer_
#define _GProcessSocketServer_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSocketServerO GProcessSocketServerO;
//===============================================
struct _GProcessSocketServerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketServer_New();
void GProcessSocketServer_Delete(GProcessO* obj);
GProcessO* GProcessSocketServer();
//===============================================
#endif
//===============================================
