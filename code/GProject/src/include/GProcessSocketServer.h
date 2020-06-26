//===============================================
#ifndef _GProcessSocketServer_
#define _GProcessSocketServer_
//===============================================
#include "GProcess.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GProcessSocketServerO GProcessSocketServerO;
//===============================================
struct _GProcessSocketServerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketServer_New();
void GProcessSocketServer_Delete();
GProcessO* GProcessSocketServer();
//===============================================
#endif
//===============================================
#endif
//===============================================
