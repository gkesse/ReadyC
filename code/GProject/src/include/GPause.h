//===============================================
#ifndef _GPause_
#define _GPause_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GPauseO GPauseO;
//===============================================
struct _GPauseO {
    void (*Delete)();
    void (*Pause)();
};
//===============================================
GPauseO* GPause_New();
void GPause_Delete();
GPauseO* GPause();
//===============================================
#endif
//===============================================