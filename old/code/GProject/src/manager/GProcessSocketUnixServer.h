//===============================================
#ifndef _GProcessSocketUnixServer_
#define _GProcessSocketUnixServer_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSocketUnixServerO GProcessSocketUnixServerO;
//===============================================
struct _GProcessSocketUnixServerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketUnixServer_New();
void GProcessSocketUnixServer_Delete();
GProcessO* GProcessSocketUnixServer();
//===============================================
#endif
//===============================================
