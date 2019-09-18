//===============================================
#ifndef _GProcessSocketUnixServerFile_
#define _GProcessSocketUnixServerFile_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSocketUnixServerFileO GProcessSocketUnixServerFileO;
//===============================================
struct _GProcessSocketUnixServerFileO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketUnixServerFile_New();
void GProcessSocketUnixServerFile_Delete();
GProcessO* GProcessSocketUnixServerFile();
//===============================================
#endif
//===============================================
