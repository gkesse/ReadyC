//===============================================
#ifndef _GProcessSocketClient_
#define _GProcessSocketClient_
//===============================================
#include "GProcess.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GProcessSocketClientO GProcessSocketClientO;
//===============================================
struct _GProcessSocketClientO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketClient_New();
void GProcessSocketClient_Delete();
GProcessO* GProcessSocketClient();
//===============================================
#endif
//===============================================
#endif
//===============================================
