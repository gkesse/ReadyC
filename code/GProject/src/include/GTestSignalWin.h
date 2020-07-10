//===============================================
#ifndef _GTestSignalWin_
#define _GTestSignalWin_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GTestSignalWinO GTestSignalWinO;
//===============================================
struct _GTestSignalWinO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
};
//===============================================
GTestSignalWinO* GTestSignalWin_New();
void GTestSignalWin_Delete();
GTestSignalWinO* GTestSignalWin();
//===============================================
#endif
//===============================================
