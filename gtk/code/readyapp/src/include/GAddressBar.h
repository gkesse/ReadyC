//===============================================
#ifndef _GAddressBar_
#define _GAddressBar_
//===============================================
#include "GInclude.h"
//===============================================
G_BEGIN_DECLS
//===============================================
#define GAddressBar_Obj(obj) \
    GTK_CHECK_CAST(obj, GAddressBar_Get_Type(), GAddressBar)
#define GAddressBar_Class(klass) \
    GTK_CHECK_CLASS_CAST(klass, GAddressBar_Get_Type(), GAddressBarClass)
#define Is_GAddressBar(obj) \
    GTK_CHECK_TYPE(obj, GAddressBar_Get_Type())
//===============================================
typedef struct _GAddressBar GAddressBar;
typedef struct _GAddressBarClass GAddressBarClass;
//===============================================
struct _GAddressBar {
    GtkBox parent;
};
//===============================================
struct _GAddressBarClass {
    GtkBoxClass parent_class;
};
//===============================================
GtkWidget* GAddressBar_New();
GtkType GAddressBar_Get_Type();
//===============================================
G_END_DECLS
//===============================================
#endif
//===============================================