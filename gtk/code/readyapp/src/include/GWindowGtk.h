//===============================================
#ifndef _GWindowGtk_
#define _GWindowGtk_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
G_BEGIN_DECLS
//===============================================
#define GWindowGtk_Obj(obj) \
    GTK_CHECK_CAST(obj, GWindowGtk_Get_Type(), GWindowGtk)
#define GWindowGtk_Class(klass) \
    GTK_CHECK_CLASS_CAST(klass, GWindowGtk_Get_Type(), GWindowGtkClass)
#define Is_GWindowGtk(obj) \
    GTK_CHECK_TYPE(obj, GWindowGtk_Get_Type())
//===============================================
typedef struct _GWindowGtk GWindowGtk;
typedef struct _GWindowGtkClass GWindowGtkClass;
//===============================================
struct _GWindowGtk {
    GtkWindow parent;
};
//===============================================
struct _GWindowGtkClass {
    GtkWindowClass parent_class;
};
//===============================================
GtkWidget* GWindowGtk_New();
GtkType GWindowGtk_Get_Type();
//===============================================
G_END_DECLS
//===============================================
#endif
//===============================================