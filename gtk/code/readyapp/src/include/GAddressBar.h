//===============================================
#ifndef _GAddressBar_
#define _GAddressBar_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GAddressBarO GAddressBarO;
//===============================================
struct _GAddressBarO {
    void* parent;
};
//===============================================
GWidgetO* GAddressBar_New();
void GAddressBar_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================