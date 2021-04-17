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
    int currentKeyFlag;
    char* defaultKey;
    char* currentKey;
    void* widgetMap;
    void* titleMap;
};
//===============================================
GWidgetO* GStackWidget_New();
void GStackWidget_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================