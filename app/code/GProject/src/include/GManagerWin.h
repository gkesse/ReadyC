//===============================================
#ifndef _GManagerWin_
#define _GManagerWin_
//===============================================
#include "GManager.h"
//===============================================
typedef struct _GManagerWinO GManagerWinO;
//===============================================
struct _GManagerWinO {
    void* parent;
    void (*Delete)();
};
//===============================================
GManagerO* GManagerWin_New();
void GManagerWin_Delete();
GManagerO* GManagerWin();
//===============================================
#endif
//===============================================