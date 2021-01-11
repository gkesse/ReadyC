//===============================================
#ifndef _GWindow_
#define _GWindow_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
G_BEGIN_DECLS
//===============================================
#define GWindow_Obj(obj) \
    GTK_CHECK_CAST(obj, GWindow_Get_Type(), GWindow)
#define GWindow_Class(klass) \
    GTK_CHECK_CLASS_CAST(klass, GWindow_Get_Type(), GWindowClass)
#define Is_GWindow(obj) \
    GTK_CHECK_TYPE(obj, GWindow_Get_Type())
//===============================================
typedef struct _GWindow GWindow;
typedef struct _GWindowClass GWindowClass;
//===============================================
struct _GWindow {
    GtkBox parent;
};
//===============================================
struct _GWindowClass {
    GtkBoxClass parent_class;
};
//===============================================
GtkWidget* GWindow_New();
GtkType GWindow_Get_Type();
//===============================================
G_END_DECLS
//===============================================
#endif
//===============================================