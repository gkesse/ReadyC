//===============================================
#ifndef _GProcessSocketUnixClientFile_
#define _GProcessSocketUnixClientFile_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSocketUnixClientFileO GProcessSocketUnixClientFileO;
//===============================================
struct _GProcessSocketUnixClientFileO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSocketUnixClientFile_New();
void GProcessSocketUnixClientFile_Delete();
GProcessO* GProcessSocketUnixClientFile();
//===============================================
#endif
//===============================================
