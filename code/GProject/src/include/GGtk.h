//===============================================
#ifndef _GGtk_
#define _GGtk_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GGtkO GGtkO;
//===============================================
struct _GGtkO {
    void (*Delete)(); 
    void (*Test)(int argc, char** argv);
};
//===============================================
GGtkO* GGtk_New();
void GGtk_Delete();
GGtkO* GGtk();
//===============================================
#endif
//===============================================
