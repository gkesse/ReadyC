//===============================================
#ifndef _GAddressKey_
#define _GAddressKey_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GAddressKeyO GAddressKeyO;
//===============================================
struct _GAddressKeyO {
    void* parent;
};
//===============================================
GWidgetO* GAddressKey_New();
void GAddressKey_Delete(GWidgetO* obj);
//===============================================
#endif
//===============================================