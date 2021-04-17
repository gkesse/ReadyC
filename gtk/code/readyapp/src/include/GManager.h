//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
#include "GWidget.h"
//===============================================
#define GFORMAT_SIZE (1024)
//===============================================
typedef struct _GManagerO GManagerO;
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
//===============================================
struct _GManagerO {
    void (*Delete)();
    // data
    void (*LoadData)();
    void (*ShowData)(void* data);
    void (*ShowList)(void* data);
    void (*ShowMap)(void* data);
    // string
    char* (*CopyStr)(const char* strIn);
    void* (*Split)(char* strIn, char* sep);
    char* (*Trim)(char* strIn);
    char* (*TrimLeft)(char* strIn);
    char* (*TrimRight)(char* strIn);
    int (*GetWidth)(char* widthMap, int index, int defaultWidth);
    int (*IsNumber)(char* strIn);
    char* (*Format)(const char* format, ...);
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
    GtkWidget* (*Button)(char* icon, char* text, int space, int font);
    GtkWidget* (*Button2)(char* img, int scale, int width, int height, char* text, int space);
    // space
    GtkWidget* (*SpaceH)(int space);
    GtkWidget* (*SpaceV)(int space);
    // terminal
    void (*ReadLine)(char* buffer, int size);
    // free
    void (*Free)(void* buffer);
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
    // format
    char format[GFORMAT_SIZE+1];
    // title
    GtkWidget* title;
    // address
    GtkWidget* address_bar;
    GWidgetO* address_key;
    // page
    GWidgetO* page_map;
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
    // sqlite
    char* sqlite_db_path;
    // log
    char* log_on;
    char* log_mode;
    char* log_path;
};
//===============================================
#endif
//===============================================