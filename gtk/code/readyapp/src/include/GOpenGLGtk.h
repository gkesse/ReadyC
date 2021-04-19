//===============================================
#ifndef _GOpenGLGtk_
#define _GOpenGLGtk_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GOpenGLGtkO GOpenGLGtkO;
//===============================================
struct _GOpenGLGtkO {
    void* parent;
};
//===============================================
GWidgetO* GOpenGLGtk_New();
void GOpenGLGtk_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================