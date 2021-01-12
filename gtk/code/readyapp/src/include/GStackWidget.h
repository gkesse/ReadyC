//===============================================
#ifndef _GStackWidget_
#define _GStackWidget_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GStackWidgetO GStackWidgetO;
//===============================================
struct _GStackWidgetO {
    void* parent;
    int count;
    int currentIndex;
    void* widgetMap;
};
//===============================================
GWidgetO* GStackWidget_New();
void GStackWidget_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================