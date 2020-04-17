//===============================================
#ifndef _GProcessRpcClient_
#define _GProcessRpcClient_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessRpcClientO GProcessRpcClientO;
//===============================================
struct _GProcessRpcClientO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessRpcClient_New();
void GProcessRpcClient_Delete();
GProcessO* GProcessRpcClient();
//===============================================
#endif
//===============================================
