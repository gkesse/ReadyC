//===============================================
#ifndef _GBase_
#define _GBase_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GBaseO GBaseO;
//===============================================
struct _GBaseO {
    void (*Delete)();
    int (*FromBinary)(char* binary);
    void (*ToBinary)(const int decimal, char* binary);
};
//===============================================
GBaseO* GBase_New();
void GBase_Delete();
GBaseO* GBase();
//===============================================
#endif
//===============================================
