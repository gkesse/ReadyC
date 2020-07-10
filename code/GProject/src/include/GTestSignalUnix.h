//===============================================
#ifndef _GTestSignalUnix_
#define _GTestSignalUnix_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GTestSignalUnixO GTestSignalUnixO;
//===============================================
struct _GTestSignalUnixO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
};
//===============================================
GTestSignalUnixO* GTestSignalUnix_New();
void GTestSignalUnix_Delete();
GTestSignalUnixO* GTestSignalUnix();
//===============================================
#endif
//===============================================
