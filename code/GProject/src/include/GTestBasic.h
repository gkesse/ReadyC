//===============================================
#ifndef _GTestBasic_
#define _GTestBasic_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GTestBasicO GTestBasicO;
//===============================================
struct _GTestBasicO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
};
//===============================================
GTestBasicO* GTestBasic_New();
void GTestBasic_Delete();
GTestBasicO* GTestBasic();
//===============================================
#endif
//===============================================
