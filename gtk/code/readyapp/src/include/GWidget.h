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
    void (*AddPage)(GWidgetO* obj, char* key, char* title, GtkWidget* widget, int isDefault);
    void (*SetCurrentPage)(GWidgetO* obj, char* key);
    char* (*GetTitle)(GWidgetO* obj, char* key);
    char* (*GetDefaultKey)(GWidgetO* obj);
    int (*Count)(GWidgetO* obj);
    void (*AddItem)(GWidgetO* obj, char* key, char* text, char* icon);
    void (*AddItemClick)(GWidgetO* obj, GWidgetO* obs);
    void (*EmitItemClick)(GWidgetO* obj);
    void (*OnItemClickObs)(GWidgetO* obj);
    void (*OnItemClick)(GtkWidget* widget, gpointer params);
    //
    GtkWidget* widget;
    void* item_map;
};
//===============================================
GWidgetO* GWidget_New();
void GWidget_Delete(GWidgetO* obj);
GWidgetO* GWidget(const char* key);
//===============================================
#endif
//===============================================