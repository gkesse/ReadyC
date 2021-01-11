//===============================================
#ifndef _GWindowGtk_
#define _GWindowGtk_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GWindowGtkO GWindowGtkO;
//===============================================
struct _GWindowGtkO {
    void* parent;
};
//===============================================
GWidgetO* GWindowGtk_New();
void GWindowGtk_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================