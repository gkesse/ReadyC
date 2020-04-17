//===============================================
#ifndef _GProcessSocketUnixClientUdp_
#define _GProcessSocketUnixClientUdp_
//===============================================
#include "GProcess.h"
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
