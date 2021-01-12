//===============================================
#ifndef _GListBox_
#define _GListBox_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GListBoxO GListBoxO;
//===============================================
struct _GListBoxO {
    void* parent;
    void* widgetMap;
};
//===============================================
GWidgetO* GListBox_New();
void GListBox_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================