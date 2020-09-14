//===============================================
#ifndef _GDateUi_
#define _GDateUi_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDateUiO GDateUiO;
//===============================================
struct _GDateUiO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
    char* G_STATE;
};
//===============================================
GDateUiO* GDateUi_New();
void GDateUi_Delete();
GDateUiO* GDateUi();
//===============================================
#endif
//===============================================