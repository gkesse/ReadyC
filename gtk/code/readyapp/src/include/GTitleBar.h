//===============================================
#ifndef _GTitleBar_
#define _GTitleBar_
//===============================================
#include "GInclude.h"
//===============================================
G_BEGIN_DECLS
//===============================================
#define GTitleBar_Obj(obj) \
    GTK_CHECK_CAST(obj, GTitleBar_Get_Type(), GTitleBar)
#define GTitleBar_Class(klass) \
    GTK_CHECK_CLASS_CAST(klass, GTitleBar_Get_Type(), GTitleBarClass)
#define Is_GTitleBar(obj) \
    GTK_CHECK_TYPE(obj, GTitleBar_Get_Type())
//===============================================
typedef struct _GTitleBar GTitleBar;
typedef struct _GTitleBarClass GTitleBarClass;
//===============================================
struct _GTitleBar {
    GtkBox parent;
};
//===============================================
struct _GTitleBarClass {
    GtkBoxClass parent_class;
};
//===============================================
GtkWidget* GTitleBar_New();
GtkType GTitleBar_Get_Type();
//===============================================
G_END_DECLS
//===============================================
#endif
//===============================================