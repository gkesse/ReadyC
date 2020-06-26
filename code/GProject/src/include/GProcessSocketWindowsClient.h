//===============================================
#ifndef _GProcessSocketWindowsClient_
#define _GProcessSocketWindowsClient_
//===============================================
#include "GProcess.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GProcessSocketWindowsClientO GProcessSocketWindowsClientO;
//===============================================
struct _GProcessSocketWindowsClientO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketWindowsClient_New();
void GProcessSocketWindowsClient_Delete();
GProcessO* GProcessSocketWindowsClient();
//===============================================
#endif
//===============================================
#endif
//===============================================
