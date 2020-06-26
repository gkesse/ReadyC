//===============================================
#ifndef _GProcessSocketUnixClientUdp_
#define _GProcessSocketUnixClientUdp_
//===============================================
#include "GProcess.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GProcessSocketUnixClientUdpO GProcessSocketUnixClientUdpO;
//===============================================
struct _GProcessSocketUnixClientUdpO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketUnixClientUdp_New();
void GProcessSocketUnixClientUdp_Delete();
GProcessO* GProcessSocketUnixClientUdp();
//===============================================
#endif
//===============================================
#endif
//===============================================
