//===============================================
#ifndef _GThread2_
#define _GThread2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GThread2O GThread2O;
//===============================================
struct _GThread2O {
    void (*Delete)();
    int (*FromBinary)(char* binary);
    void (*ToBinary)(const int decimal, char* binary);
};
//===============================================
GThread2O* GThread2_New();
void GThread2_Delete();
GThread2O* GThread2();
//===============================================
#endif
//===============================================
