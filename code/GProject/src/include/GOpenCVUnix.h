//===============================================
#ifndef _GOpenCVUnix_
#define _GOpenCVUnix_
//===============================================
#include "GOpenCV.h"
//===============================================
#if defined(__unix)
//===============================================
typedef struct _GOpenCVUnixO GOpenCVUnixO;
//===============================================
struct _GOpenCVUnixO {
    void* parent;
    void (*Delete)(); 
    void (*Open)();
};
//===============================================
GOpenCVO* GOpenCVUnix_New();
void GOpenCVUnix_Delete();
GOpenCVO* GOpenCVUnix();
//===============================================
#endif
//===============================================
#endif
//===============================================
