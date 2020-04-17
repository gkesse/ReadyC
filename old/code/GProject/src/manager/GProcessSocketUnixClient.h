//===============================================
#ifndef _GProcessSocketUnixClient_
#define _GProcessSocketUnixClient_
//===============================================
#include "GProcess.h"
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
