//===============================================
#ifndef _GTestThreadUnix_
#define _GTestThreadUnix_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GTestThreadUnixO GTestThreadUnixO;
//===============================================
struct _GTestThreadUnixO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
};
//===============================================
GTestThreadUnixO* GTestThreadUnix_New();
void GTestThreadUnix_Delete();
GTestThreadUnixO* GTestThreadUnix();
//===============================================
#endif
//===============================================
