//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GWidgetO GWidgetO;
//===============================================
struct _GWidgetO {
    void* child;
    //
    void (*Delete)(GWidgetO* obj);
    void (*SetContent)(GWidgetO* obj, char* text);
    void (*AddWidget)(GWidgetO* obj, GtkWidget* widget);
    void (*SetCurrentIndex)(GWidgetO* obj, int index);
    int (*Count)(GWidgetO* obj);
    void (*AddItem)(GWidgetO* obj, char* key, char* text);
    void (*End)(GWidgetO* obj);
    //
    GtkWidget* widget;
};
//===============================================
GWidgetO* GWidget_New();
void GWidget_Delete(GWidgetO* obj);
GWidgetO* GWidget(const char* key);
//===============================================
#endif
//===============================================