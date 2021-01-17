//===============================================
#ifndef _GOpenCVGtk_
#define _GOpenCVGtk_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GOpenCVGtkO GOpenCVGtkO;
//===============================================
struct _GOpenCVGtkO {
    void* parent;
};
//===============================================
GWidgetO* GOpenCVGtk_New();
void GOpenCVGtk_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================