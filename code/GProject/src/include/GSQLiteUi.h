//===============================================
#ifndef _GSQLiteUi_
#define _GSQLiteUi_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSQLiteUiO GSQLiteUiO;
//===============================================
struct _GSQLiteUiO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
    char* G_STATE;
};
//===============================================
GSQLiteUiO* GSQLiteUi_New();
void GSQLiteUi_Delete();
GSQLiteUiO* GSQLiteUi();
//===============================================
#endif
//===============================================