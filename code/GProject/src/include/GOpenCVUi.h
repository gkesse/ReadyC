//===============================================
#ifndef _GOpenCVUi_
#define _GOpenCVUi_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GOpenCVUiO GOpenCVUiO;
//===============================================
struct _GOpenCVUiO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
    char* G_STATE;
};
//===============================================
GOpenCVUiO* GOpenCVUi_New();
void GOpenCVUi_Delete();
GOpenCVUiO* GOpenCVUi();
//===============================================
#endif
//===============================================