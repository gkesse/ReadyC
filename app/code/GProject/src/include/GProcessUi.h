//===============================================
#ifndef _GProcessUi_
#define _GProcessUi_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GProcessUiO GProcessUiO;
//===============================================
struct _GProcessUiO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
    char* G_STATE;
};
//===============================================
GProcessUiO* GProcessUi_New();
void GProcessUi_Delete();
GProcessUiO* GProcessUi();
//===============================================
#endif
//===============================================