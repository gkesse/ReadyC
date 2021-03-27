//===============================================
#ifndef _GSQLitePc_
#define _GSQLitePc_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSQLitePcO GSQLitePcO;
//===============================================
struct _GSQLitePcO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
};
//===============================================
GSQLitePcO* GSQLitePc_New();
void GSQLitePc_Delete();
GSQLitePcO* GSQLitePc();
//===============================================
#endif
//===============================================