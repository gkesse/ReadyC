//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
//===============================================
G_BEGIN_DECLS
//===============================================
#define GWidget_Obj(obj) \
    GTK_CHECK_CAST(obj, GWidget_Get_Type(), GWidget)
#define GWidget_Class(klass) \
    GTK_CHECK_CLASS_CAST(klass, GWidget_Get_Type(), GWidgetClass)
#define Is_GWidget(obj) \
    GTK_CHECK_TYPE(obj, GWidget_Get_Type())
//===============================================
typedef struct _GWidget GWidget;
typedef struct _GWidgetClass GWidgetClass;
//===============================================
struct _GWidget {
    GtkWidget parent;
    GtkBox parent2;
    GtkWindow parent3;
    void (*SetContent)(GWidget* widget, char* text);
};
//===============================================
struct _GWidgetClass {
    GtkWidgetClass parent_class;
    GtkBoxClass parent_class2;
    GtkWindowClass parent_class3;
};
//===============================================
GWidget* GWidget_New();
GtkType GWidget_Get_Type();
//===============================================
GWidget* GWidget_Create(char* key);
//===============================================
G_END_DECLS
//===============================================
#endif
//===============================================