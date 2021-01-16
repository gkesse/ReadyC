//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
typedef struct _GManagerO GManagerO;
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
//===============================================
struct _GManagerO {
    void (*Delete)();
    // data
    sGManager* (*GetData)();
    void (*LoadData)();
    // string
    char* (*CopyStr)(const char* strIn);
    int (*SplitCount)(char* strIn, char* sep);
    void (*SplitGet)(char* strIn, char* strOut, char* sep, int index);
    // page
    void (*SetPage)(char* address);
    // layout
    void (*ClearLayout)(GtkWidget* layout);
    // widget
    void (*SetColor)(char* key, GtkWidget* widget, char* color, int state);
    // font
    void (*SetFont)(GtkWidget* widget, char* font);
    // style
    void (*LoadStyle)();
    // env
    char* (*GetEnv)(char* key);
    // img
    void (*LoadImg)();
    GtkWidget* (*GetImg)(char* img, int scale, int width, int height);
    // picto
    void (*LoadPicto)();
    char* (*GetPicto)(char* key);
    // button
    GtkWidget* (*Button)(char* icon, char* text, int space);
    GtkWidget* (*Button2)(char* img, int scale, int width, int height, char* text, int space);
    // space
    GtkWidget* (*SpaceH)(int space);
    GtkWidget* (*SpaceV)(int space);
    // struct
    sGManager* mgr;
};
//===============================================
GManagerO* GManager_New();
void GManager_Delete();
GManagerO* GManager();
//===============================================
// struct
//===============================================
struct _sGManager {
    sGApp* app;
};
//===============================================
struct _sGApp {
    // app
    char* app_name;
    // win
    int win_width;
    int win_height;
    // string
    char format[256];
    // title
    GtkWidget* title;
    void* title_map;
    // address
    GWidgetO* address_key;
    // page
    GWidgetO* page_map;
    void* page_id;
    // widget
    char* widget_id;
    // color
    char* bg_color;
    // style
    char* style_path;
    // img
    char* img_path;
    void* img_map;
    // picto
    void* picto_map;
    // path
    char* path_sep;
};
//===============================================
#endif
//===============================================