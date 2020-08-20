//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GProcessO GProcessO;
typedef struct _GMapO_GProcess_GCHAR_PTR_GVOID_PTR GMapO_GProcess_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GProcessO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
    char* G_STATE;
};
//===============================================
GProcessO* GProcess_New();
void GProcess_Delete();
GProcessO* GProcess();
//===============================================
#endif
//===============================================