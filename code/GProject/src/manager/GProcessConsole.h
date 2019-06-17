//===============================================
#ifndef _GProcessConsole_
#define _GProcessConsole_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessConsoleO GProcessConsoleO;
//===============================================
struct _GProcessConsoleO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessConsole_New();
void GProcessConsole_Delete(GProcessO* obj);
GProcessO* GProcessConsole();
//===============================================
#endif
//===============================================
