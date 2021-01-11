//===============================================
#ifndef _GAddressKey_
#define _GAddressKey_
//===============================================
#include "GInclude.h"
//===============================================
G_BEGIN_DECLS
//===============================================
#define GAddressKey_Obj(obj) \
    GTK_CHECK_CAST(obj, GAddressKey_Get_Type(), GAddressKey)
#define GAddressKey_Class(klass) \
    GTK_CHECK_CLASS_CAST(klass, GAddressKey_Get_Type(), GAddressKeyClass)
#define Is_GAddressKey(obj) \
    GTK_CHECK_TYPE(obj, GAddressKey_Get_Type())
//===============================================
typedef struct _GAddressKey GAddressKey;
typedef struct _GAddressKeyClass GAddressKeyClass;
//===============================================
struct _GAddressKey {
    GtkBox parent;
};
//===============================================
struct _GAddressKeyClass {
    GtkBoxClass parent_class;
};
//===============================================
GtkWidget* GAddressKey_New();
GtkType GAddressKey_Get_Type();
//===============================================
G_END_DECLS
//===============================================
#endif
//===============================================