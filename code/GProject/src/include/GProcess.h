//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GProcessO GProcessO;
//===============================================
struct _GProcessO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
    void (*Test)(int argc, char** argv);
};
//===============================================
GProcessO* GProcess_New();
void GProcess_Delete();
GProcessO* GProcess();
//===============================================
#endif
//===============================================