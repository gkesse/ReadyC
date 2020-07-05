//===============================================
#ifndef _GGtk_
#define _GGtk_
//===============================================
#include "GInclude.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
typedef struct _GGtkO GGtkO;
//===============================================
struct _GGtkO {
    void (*Delete)();
    void (*Test)(int argc, char** argv);
    sGArgMap* m_argMap;
    char m_builderPath[256];
};
//===============================================
GGtkO* GGtk_New();
void GGtk_Delete();
GGtkO* GGtk();
//===============================================
#endif
//===============================================
#endif
//===============================================
