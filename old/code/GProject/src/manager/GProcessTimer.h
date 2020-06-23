//===============================================
#ifndef _GProcessTimer_
#define _GProcessTimer_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessTimerO GProcessTimerO;
//===============================================
struct _GProcessTimerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessTimer_New();
void GProcessTimer_Delete();
GProcessO* GProcessTimer();
//===============================================
#endif
//===============================================
