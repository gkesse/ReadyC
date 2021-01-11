//===============================================
#ifndef _GManagerUnix_
#define _GManagerUnix_
//===============================================
#include "GManager.h"
//===============================================
typedef struct _GManagerUnixO GManagerUnixO;
//===============================================
struct _GManagerUnixO {
    void* parent;
    void (*Delete)();
};
//===============================================
GManagerO* GManagerUnix_New();
void GManagerUnix_Delete();
GManagerO* GManagerUnix();
//===============================================
#endif
//===============================================