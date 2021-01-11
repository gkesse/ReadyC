//===============================================
#ifndef _GTitleBar_
#define _GTitleBar_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GTitleBarO GTitleBarO;
//===============================================
struct _GTitleBarO {
    void* parent;
};
//===============================================
GWidgetO* GTitleBar_New();
void GTitleBar_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================