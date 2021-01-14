//===============================================
#ifndef _GPicto_
#define _GPicto_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GPictoO GPictoO;
//===============================================
struct _GPictoO {
    void (*Delete)();
    void (*Load)();
    char* (*Get)(char* key);
};
//===============================================
GPictoO* GPicto_New();
void GPicto_Delete();
GPictoO* GPicto();
//===============================================
#endif
//===============================================