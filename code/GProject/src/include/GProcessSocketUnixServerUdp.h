//===============================================
#ifndef _GProcessSocketUnixServerUdp_
#define _GProcessSocketUnixServerUdp_
//===============================================
#include "GProcess.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GProcessSocketUnixServerUdpO GProcessSocketUnixServerUdpO;
//===============================================
struct _GProcessSocketUnixServerUdpO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketUnixServerUdp_New();
void GProcessSocketUnixServerUdp_Delete();
GProcessO* GProcessSocketUnixServerUdp();
//===============================================
#endif
//===============================================
#endif
//===============================================