//===============================================
#ifndef _GWindow_
#define _GWindow_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GWindowO GWindowO;
//===============================================
struct _GWindowO {
    void* parent;
    GWidgetO* pageMap;
    void* pageId;
    void* titleMap;
};
//===============================================
GWidgetO* GWindow_New();
void GWindow_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================