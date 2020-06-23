//===============================================
#ifndef _GProcessKeyboard_
#define _GProcessKeyboard_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessKeyboardO GProcessKeyboardO;
//===============================================
struct _GProcessKeyboardO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessKeyboard_New();
void GProcessKeyboard_Delete();
GProcessO* GProcessKeyboard();
//===============================================
#endif
//===============================================
