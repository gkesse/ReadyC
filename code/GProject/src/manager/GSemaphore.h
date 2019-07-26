//===============================================
#ifndef _GSemaphore_
#define _GSemaphore_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSemaphoreO GSemaphoreO;
//===============================================
struct _GSemaphoreO {
    void (*Delete)();
    int (*FromBinary)(char* binary);
    void (*ToBinary)(const int decimal, char* binary);
};
//===============================================
GSemaphoreO* GSemaphore_New();
void GSemaphore_Delete();
GSemaphoreO* GSemaphore();
//===============================================
#endif
//===============================================
