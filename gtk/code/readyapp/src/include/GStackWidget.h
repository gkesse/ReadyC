//===============================================
#ifndef _GStackWidget_
#define _GStackWidget_
//===============================================
#include "GInclude.h"
//===============================================
G_BEGIN_DECLS
//===============================================
#define GStackWidget_Obj(obj) \
    GTK_CHECK_CAST(obj, GStackWidget_Get_Type(), GStackWidget)
#define GStackWidget_Class(klass) \
    GTK_CHECK_CLASS_CAST(klass, GStackWidget_Get_Type(), GStackWidgetClass)
#define Is_GStackWidget(obj) \
    GTK_CHECK_TYPE(obj, GStackWidget_Get_Type())
//===============================================
typedef struct _GStackWidget GStackWidget;
typedef struct _GStackWidgetClass GStackWidgetClass;
//===============================================
struct _GStackWidget {
    GtkBox parent;
};
//===============================================
struct _GStackWidgetClass {
    GtkBoxClass parent_class;
};
//===============================================
GtkWidget* GStackWidget_New();
GtkType GStackWidget_Get_Type();
//===============================================
G_END_DECLS
//===============================================
#endif
//===============================================