//===============================================
#ifndef _GTestThreadWin_
#define _GTestThreadWin_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GTestThreadWinO GTestThreadWinO;
//===============================================
struct _GTestThreadWinO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
};
//===============================================
GTestThreadWinO* GTestThreadWin_New();
void GTestThreadWin_Delete();
GTestThreadWinO* GTestThreadWin();
//===============================================
#endif
//===============================================
