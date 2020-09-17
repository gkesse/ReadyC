//===============================================
#ifndef _GGtkUi_
#define _GGtkUi_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GGtkUiO GGtkUiO;
//===============================================
struct _GGtkUiO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
    char* G_STATE;
};
//===============================================
GGtkUiO* GGtkUi_New();
void GGtkUi_Delete();
GGtkUiO* GGtkUi();
//===============================================
#endif
//===============================================