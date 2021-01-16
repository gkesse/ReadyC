//===============================================
#ifndef _GOpenCVUi_
#define _GOpenCVUi_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GOpenCVUiO GOpenCVUiO;
//===============================================
struct _GOpenCVUiO {
    void* parent;
};
//===============================================
GWidgetO* GOpenCVUi_New();
void GOpenCVUi_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================