//===============================================
#ifndef _GSQLiteUi_
#define _GSQLiteUi_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GSQLiteUiO GSQLiteUiO;
//===============================================
struct _GSQLiteUiO {
    void* parent;
};
//===============================================
GWidgetO* GSQLiteUi_New();
void GSQLiteUi_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================