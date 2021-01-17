//===============================================
#ifndef _GSQLiteGtk_
#define _GSQLiteGtk_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GSQLiteGtkO GSQLiteGtkO;
//===============================================
struct _GSQLiteGtkO {
    void* parent;
};
//===============================================
GWidgetO* GSQLiteGtk_New();
void GSQLiteGtk_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================