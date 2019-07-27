//===============================================
#ifndef _GProcessSocketWindowsServer_
#define _GProcessSocketWindowsServer_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSocketWindowsServerO GProcessSocketWindowsServerO;
//===============================================
struct _GProcessSocketWindowsServerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketWindowsServer_New();
void GProcessSocketWindowsServer_Delete();
GProcessO* GProcessSocketWindowsServer();
//===============================================
#endif
//===============================================
