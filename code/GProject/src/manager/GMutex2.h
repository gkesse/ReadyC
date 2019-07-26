//===============================================
#ifndef _GMutex2_
#define _GMutex2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GMutex2O GMutex2O;
//===============================================
struct _GMutex2O {
    void (*Delete)();
    int (*FromBinary)(char* binary);
    void (*ToBinary)(const int decimal, char* binary);
};
//===============================================
GMutex2O* GMutex2_New();
void GMutex2_Delete();
GMutex2O* GMutex2();
//===============================================
#endif
//===============================================
