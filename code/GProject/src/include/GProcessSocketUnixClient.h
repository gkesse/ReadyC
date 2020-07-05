//===============================================
#ifndef _GProcessSocketUnixClient_
#define _GProcessSocketUnixClient_
//===============================================
#include "GProcess.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GProcessSocketUnixClientO GProcessSocketUnixClientO;
//===============================================
struct _GProcessSocketUnixClientO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketUnixClient_New();
void GProcessSocketUnixClient_Delete();
GProcessO* GProcessSocketUnixClient();
//===============================================
#endif
//===============================================
#endif
//===============================================
