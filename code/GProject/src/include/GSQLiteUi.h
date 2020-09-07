//===============================================
#ifndef _GSQLiteUi_
#define _GSQLiteUi_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSQLiteUiO GSQLiteUiO;
typedef struct _GMapO_GSQLiteUi_GCHAR_PTR_GVOID_PTR GMapO_GSQLiteUi_GCHAR_PTR_GVOID_PTR;
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