//===============================================
#ifndef _GProcessSocketWindowsClient_
#define _GProcessSocketWindowsClient_
//===============================================
#include "GProcess.h"
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
