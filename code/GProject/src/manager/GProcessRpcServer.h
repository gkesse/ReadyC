//===============================================
#ifndef _GProcessRpcServer_
#define _GProcessRpcServer_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessRpcServerO GProcessRpcServerO;
//===============================================
struct _GProcessRpcServerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessRpcServer_New();
void GProcessRpcServer_Delete();
GProcessO* GProcessRpcServer();
//===============================================
#endif
//===============================================
