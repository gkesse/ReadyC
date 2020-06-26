//===============================================
#ifndef _GProcessFork_
#define _GProcessFork_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GProcessForkO GProcessForkO;
//===============================================
struct _GProcessForkO {
    void (*Delete)();
    void (*Test)(int argc, char** argv);
};
//===============================================
GProcessForkO* GProcessFork_New();
void GProcessFork_Delete();
GProcessForkO* GProcessFork();
//===============================================
#endif
//===============================================
